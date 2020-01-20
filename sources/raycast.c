/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/20 14:50:34 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void draw_floor(t_env *env)
{
    if(env->side == 0)
    {
    	env->floorx_wall = env->mapX;
        env->floory_wall = env->mapY + env->wallX;
    }
    else if(env->side == 2)
    {
        env->floorx_wall = env->mapX + 1.0;
        env->floory_wall = env->mapY + env->wallX;
    }
    else if(env->side == 1)
    {
        env->floorx_wall = env->mapX + env->wallX;
        env->floory_wall = env->mapY;
    }
    else
    {
        env->floorx_wall = env->mapX + env->wallX;
        env->floory_wall = env->mapY + 1.0;
    }
    env->dist_wall = env->perpWallDist;
    env->dist_player = 0.0;
    if (env->drawEnd < 0)
		env->drawEnd = env->resY; 
	env->y = env->drawEnd;
    while (env->y < env->resY)
	{
		env->current_dist = env->resY / (2.0 * env->y - env->resY);
		env->weight = (env->current_dist - env->dist_player) / (env->dist_wall - env->dist_player);
		env->current_floorx = env->weight * env->floorx_wall + (1.0 - env->weight) * env->posX;
		env->current_floory = env->weight * env->floory_wall + (1.0 - env->weight) * env->posY;
		env->ceil_textx = (int)(env->current_floorx * env->textC->width) % env->textC->width;
		env->ceil_texty = (int)(env->current_floory * env->textC->height) % env->textC->height;
		env->floor_textx = (int)(env->current_floorx * env->textF->width) % env->textF->width;
		env->floor_texty = (int)(env->current_floory * env->textF->height) % env->textF->height;
		if (env->has_text_floor)
			put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->floor_textx, env->floor_texty, env->textF), env);
		else
			put_pxl_clr(env->x, env->y, env->color_floor, env);
		if (env->has_text_ceiling)
			put_pxl_clr(env->x, env->resY - env->y - 1, get_pxl_clr_value(env->ceil_textx, env->ceil_texty, env->textC), env);
		else
			put_pxl_clr(env->x, env->resY - env->y - 1, env->color_ceiling, env);
		env->y++;
	}
}

void	calc_ray(t_env *env)
{
	env->cameraX = (2 * env->x) / (double)env->resX - 1;
	env->rayDirX = env->dirX + env->planeX * env->cameraX;
	env->rayDirY = env->dirY + env->planeY * env->cameraX;
	env->deltaDistX = fabs(1 / env->rayDirX);
	env->deltaDistY = fabs(1 / env->rayDirY);
	env->mapX = (int)env->posX;
	env->mapY = (int)env->posY;
	
	if (env->rayDirX < 0)
	{
		env->stepX = -1;
		env->sideDistX = (env->posX - env->mapX) * env->deltaDistX;
	}
	else
	{
		env->stepX = 1;
		env->sideDistX = (env->mapX + 1.0 - env->posX) * env->deltaDistX;
	}
	if (env->rayDirY < 0)
	{
		env->stepY = -1;
		env->sideDistY = (env->posY - env->mapY) * env->deltaDistY;
	}
	else
	{
		env->stepY = 1;
		env->sideDistY = (env->mapY + 1.0 - env->posY) * env->deltaDistY;
	}
}

void	find_hit(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sideDistX < env->sideDistY)
		{
			env->sideDistX += env->deltaDistX;
			env->mapX += env->stepX;
			if (env->rayDirX >=0)
				env->side = 0;
			else
				env->side = 2;
		}
		else
		{
			env->sideDistY += env->deltaDistY;
			env->mapY += env->stepY;
			if (env->rayDirY >= 0)
				env->side = 1;
			else
				env->side = 3;
		}
		if (env->map[env->mapY][env->mapX] == '1')
			env->hit = 1;
	}
	calc_dist(env);
}

void	calc_dist(t_env *env)
{
	if (env->side == 0 || env->side == 2)
		env->perpWallDist = (env->mapX - env->posX + (1 - env->stepX) / 2) / env->rayDirX;
	else
		env->perpWallDist = (env->mapY - env->posY + (1 - env->stepY) / 2) / env->rayDirY;
}

void	load_draw_values(t_env *env)
{
	env->lineHeight = (int)(env->resY / env->perpWallDist);
	env->drawStart = env->resY / 2 - env->lineHeight / 2;
	if (env->drawStart < 0)
		env->drawStart = 0;
	env->drawEnd = (env->lineHeight / 2) + (env->resY / 2);
	if (env->drawEnd >= env->resY)
		env->drawEnd = env->resY - 1;
	if (env->side == 0 || env->side == 2) 
		env->wallX = env->posY + env->perpWallDist * env->rayDirY;
	else
		env->wallX = env->posX + env->perpWallDist * env->rayDirX;
	env->wallX -= floor(env->wallX);
	env->texX = (int)(env->wallX * (double)env->text[env->side]->width);
	if ((env->side == 0 || env->side == 2) && env->rayDirX > 0) 
		env->texX = env->text[env->side]->width - env->texX - 1;
	if ((env->side == 1 || env->side == 3) && env->rayDirY < 0)
		env->texX = env->text[env->side]->width - env->texX - 1;
	env->step = 1.0 * env->text[env->side]->height / env->lineHeight;
	env->texPos = (env->drawStart - env->resY / 2 + env->lineHeight / 2) * env->step;
}

void	render(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, env->resX, env->resY);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	env->x = 0;
	env->y = 0;
	while(env->x < env->resX)
	{
		env->hit = 0;
		calc_ray(env);
		find_hit(env);
		calc_dist(env);
		load_draw_values(env);
		env->y = env->drawStart;
      	while (env->y < env->drawEnd)
      	{
        	env->texY = (int)env->texPos;
        	env->texPos += env->step;
        	put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->text[env->side]->width - env->texX, env->texY, env->text[env->side]), env);
			env->y++;
      	}
		draw_floor(env);
		env->zbuffer[env->x] = env->perpWallDist;
		env->y = 0;
		env->x++;
	}
	sprite_casting(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}
