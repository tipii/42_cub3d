/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 15:20:11 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	floor_print(t_env *env)
{
	env->cellX = (int)env->floorX;
	env->cellY = (int)env->floorY;
	env->tx = (int)(env->textN->width * (env->floorX - env->cellX)) & (env->textN->width - 1);
	env->ty = (int)(env->textN->height * (env->floorY - env->cellY)) & (env->textN->height - 1);
	env->floorX += env->floorStepX;
	env->floorY += env->floorStepY;
	put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->tx, env->ty, env->textF), env);
	put_pxl_clr(env->x, env->resY - env->y - 1, get_pxl_clr_value(env->tx, env->ty, env->textC), env);
	env->x++;
}

void	floor_casting(t_env *env)
{
	while (env->y < env->resY)
	{
		env->rayDirX0 = env->dirX - env->planeX;
		env->rayDirY0 = env->dirY - env->planeY;
		env->rayDirX1 = env->dirX + env->planeX;
		env->rayDirY1 = env->dirY + env->planeY;
		env->p = env->y - env->resY / 2;
		env->posZ = 0.5 * env->resY;
		env->rowDistance = env->posZ / env->p; 
		env->floorStepX = env->rowDistance * (env->rayDirX1 - env->rayDirX0) / env->resX;
		env->floorStepY = env->rowDistance * (env->rayDirY1 - env->rayDirY0) / env->resX;
		env->floorX = env->posX + env->rowDistance * env->rayDirX0;
    	env->floorY = env->posY + env->rowDistance * env->rayDirY0;
		while (env->x < env->resX)
		{
			floor_print(env);
		}
		env->x = 0;
		env->y++;
	}
	env->x = 0;
	env->y = 0;
}

void	render(t_env *env)
{
	//TO DO -> malloc de zbuf
	// double zbuffer[env->resX];
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, env->resX, env->resY);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	env->x = 0;
	env->y = 0;
	//FLOOR CASTING
	floor_casting(env);
	//WALL CASTING
	while(env->x < env->resX)
	{
		env->hit = 0;
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
		//Check if ray has hit a wall
			if (env->map[env->mapY][env->mapX] == '1')
				env->hit = 1;
		}
		if (env->side == 0 || env->side == 2)
			env->perpWallDist = (env->mapX - env->posX + (1 - env->stepX) / 2) / env->rayDirX;
	  	else
			env->perpWallDist = (env->mapY - env->posY + (1 - env->stepY) / 2) / env->rayDirY;

		env->lineHeight = (int)(env->resY / env->perpWallDist);
		env->drawStart = env->resY / 2 - env->lineHeight / 2;
	  	if(env->drawStart < 0)
			env->drawStart = 0;
	  	env->drawEnd = (env->lineHeight / 2) + (env->resY / 2);
	  	if(env->drawEnd >= env->resY)
		  	env->drawEnd = env->resY - 1;

		// Texture Start
	  	if (env->side == 0 || env->side == 2) 
			env->wallX = env->posY + env->perpWallDist * env->rayDirY;
	  	else
			env->wallX = env->posX + env->perpWallDist * env->rayDirX;
	  	env->wallX -= floor(env->wallX);
	  	//x coordinate on the texture
	  	env->texX = (int)(env->wallX * (double)env->textS->width);

	  	if((env->side == 0 || env->side == 2) && env->rayDirX > 0) 
			env->texX = env->textS->width - env->texX - 1;
	  	if((env->side == 1 || env->side == 3) && env->rayDirY < 0)
			env->texX = env->textS->width - env->texX - 1;

		env->step = 1.0 * env->textS->height / env->lineHeight;
      	env->texPos = (env->drawStart - env->resY / 2 + env->lineHeight / 2) * env->step;
		
		env->y = env->drawStart;
      	while (env->y < env->drawEnd)
      	{
        	env->texY = (int)env->texPos & (env->textS->height - 1);
        	env->texPos += env->step;
			if (env->side == 0)
        		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->texX, env->texY, env->textE), env);
			else if (env->side == 1)
        		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->texX, env->texY, env->textS), env);
			else if (env->side == 2)
        		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->texX, env->texY, env->textW), env);
			else if (env->side == 3)
        		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->texX, env->texY, env->textN), env);
			env->y++;
      	}
		env->zbuffer[env->x] = env->perpWallDist;
		env->y = 0;
		env->x++;
	}
	sprite_casting(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}
