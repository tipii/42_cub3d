/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 14:39:03 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
