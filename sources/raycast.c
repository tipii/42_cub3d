/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:31:17 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		print_floor(t_env *env)
{
	if (env->has_text_floor)
		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->floor_textx,
			env->floor_texty, env->textf), env);
	else
		put_pxl_clr(env->x, env->y, env->color_floor, env);
	if (env->has_text_ceiling)
		put_pxl_clr(env->x, env->resy - env->y - 1,
			get_pxl_clr_value(env->ceil_textx, env->ceil_texty,
				env->textc), env);
	else
		put_pxl_clr(env->x, env->resy - env->y - 1,
			env->color_ceiling, env);
}

void		load_and_print_floor(t_env *env)
{
	env->y = env->drawend;
	while (env->y < env->resy)
	{
		env->current_dist = env->resy / (2.0 * env->y - env->resy);
		env->weight = (env->current_dist - env->dist_player) /
			(env->dist_wall - env->dist_player);
		env->current_floorx = env->weight * env->floorx_wall +
			(1.0 - env->weight) * env->posx;
		env->current_floory = env->weight * env->floory_wall +
			(1.0 - env->weight) * env->posy;
		env->ceil_textx = (int)(env->current_floorx * env->textc->width)
			% env->textc->width;
		env->ceil_texty = (int)(env->current_floory * env->textc->height)
			% env->textc->height;
		env->floor_textx = (int)(env->current_floorx * env->textf->width)
			% env->textf->width;
		env->floor_texty = (int)(env->current_floory * env->textf->height)
			% env->textf->height;
		print_floor(env);
		env->y++;
	}
}

void		draw_floor(t_env *env)
{
	if (env->side == 0)
	{
		env->floorx_wall = env->mapx;
		env->floory_wall = env->mapy + env->wallx;
	}
	else if (env->side == 2)
	{
		env->floorx_wall = env->mapx + 1.0;
		env->floory_wall = env->mapy + env->wallx;
	}
	else if (env->side == 1)
	{
		env->floorx_wall = env->mapx + env->wallx;
		env->floory_wall = env->mapy;
	}
	else
	{
		env->floorx_wall = env->mapx + env->wallx;
		env->floory_wall = env->mapy + 1.0;
	}
	env->dist_wall = env->perpwalldist;
	env->dist_player = 0.0;
	if (env->drawend < 0)
		env->drawend = env->resy;
	load_and_print_floor(env);
}

void		load_calc_ray_values(t_env *env)
{
	env->camerax = (2 * env->x) / (double)env->resx - 1;
	env->raydirx = env->dirx + env->planex * env->camerax;
	env->raydiry = env->diry + env->planey * env->camerax;
	env->deltadistx = fabs(1 / env->raydirx);
	env->deltadisty = fabs(1 / env->raydiry);
	env->mapx = (int)env->posx;
	env->mapy = (int)env->posy;
}

void		calc_ray(t_env *env)
{
	load_calc_ray_values(env);
	if (env->raydirx < 0)
	{
		env->stepx = -1;
		env->sidedistx = (env->posx - env->mapx) * env->deltadistx;
	}
	else
	{
		env->stepx = 1;
		env->sidedistx = (env->mapx + 1.0 - env->posx) * env->deltadistx;
	}
	if (env->raydiry < 0)
	{
		env->stepy = -1;
		env->sidedisty = (env->posy - env->mapy) * env->deltadisty;
	}
	else
	{
		env->stepy = 1;
		env->sidedisty = (env->mapy + 1.0 - env->posy) * env->deltadisty;
	}
}

void		find_hit(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sidedistx < env->sidedisty)
		{
			env->sidedistx += env->deltadistx;
			env->mapx += env->stepx;
			if (env->raydirx >= 0)
				env->side = 0;
			else
				env->side = 2;
		}
		else
		{
			env->sidedisty += env->deltadisty;
			env->mapy += env->stepy;
			if (env->raydiry >= 0)
				env->side = 1;
			else
				env->side = 3;
		}
		if (env->map[env->mapy][env->mapx] == '1')
			env->hit = 1;
	}
	calc_dist(env);
}

void		calc_dist(t_env *env)
{
	if (env->side == 0 || env->side == 2)
		env->perpwalldist = (env->mapx - env->posx + (1 - env->stepx) / 2)
		/ env->raydirx;
	else
		env->perpwalldist = (env->mapy - env->posy + (1 - env->stepy) / 2)
		/ env->raydiry;
}

void		load_draw_values(t_env *env)
{
	env->lineheight = (int)(env->resy / env->perpwalldist);
	env->drawstart = env->resy / 2 - env->lineheight / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = (env->lineheight / 2) + (env->resy / 2);
	if (env->drawend >= env->resy)
		env->drawend = env->resy - 1;
	if (env->side == 0 || env->side == 2)
		env->wallx = env->posy + env->perpwalldist * env->raydiry;
	else
		env->wallx = env->posx + env->perpwalldist * env->raydirx;
	env->wallx -= floor(env->wallx);
	env->texx = (int)(env->wallx * (double)env->text[env->side]->width);
	if ((env->side == 0 || env->side == 2) && env->raydirx > 0)
		env->texx = env->text[env->side]->width - env->texx - 1;
	if ((env->side == 1 || env->side == 3) && env->raydiry < 0)
		env->texx = env->text[env->side]->width - env->texx - 1;
	env->step = 1.0 * env->text[env->side]->height / env->lineheight;
	env->texpos = (env->drawstart - env->resy / 2 + env->lineheight / 2)
		* env->step;
}

void		draw_wall(t_env *env)
{
	env->y = env->drawstart;
	while (env->y < env->drawend)
	{
		env->texy = (int)env->texpos;
		env->texpos += env->step;
		put_pxl_clr(env->x, env->y,
			get_pxl_clr_value(env->text[env->side]->width - env->texx,
				env->texy, env->text[env->side]), env);
		env->y++;
	}
}

void		render(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, env->resx, env->resy);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp,
		&env->size_line, &env->endian);
	env->x = 0;
	env->y = 0;
	while (env->x < env->resx)
	{
		env->hit = 0;
		calc_ray(env);
		find_hit(env);
		calc_dist(env);
		load_draw_values(env);
		draw_wall(env);
		draw_floor(env);
		env->zbuffer[env->x] = env->perpwalldist;
		env->y = 0;
		env->x++;
	}
	sprite_casting(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}
