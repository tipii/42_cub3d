/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2019/12/06 17:33:29 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, env->resX, env->resY);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	env->x = 0;

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
		//perform DDA

		while (env->hit == 0)
		{
		//jump to next map square, OR in x-direction, OR in y-direction
			if (env->sideDistX < env->sideDistY)
			{
				env->sideDistX += env->deltaDistX;
				env->mapX += env->stepX;
				env->side = 0;
			}
			else
			{
				env->sideDistY += env->deltaDistY;
				env->mapY += env->stepY;
				env->side = 1;
			}
		//Check if ray has hit a wall
			if (env->map[env->mapY][env->mapX] > '0')
				env->hit = 1;
		}
		if (env->side == 0)
			env->perpWallDist = (env->mapX - env->posX + (1 - env->stepX) / 2) / env->rayDirX;
	  	else
			env->perpWallDist = (env->mapY - env->posY + (1 - env->stepY) / 2) / env->rayDirY;

		// printf("x : %d | ", env->x);
		// printf("map x :%d | ", env->mapX);
		// printf("map x :%d | ", env->mapY);
		// printf("posX %f | ", env->posX);
		// printf("posY %f | ", env->posY);
		// printf("stepX %d | ", env->stepX);
		// printf("stepY %d | ", env->stepY);
		// printf("raydirx :%f | ", env->rayDirX);
		// printf("raydiry :%f | ", env->rayDirY);

		// printf("wall dist : %f\n", env->perpWallDist);
		// printf("\n");


		env->lineHeight = (int)(env->resY / env->perpWallDist);
		// printf("resY :%d, lineheight : %d | ", env->resY, env->lineHeight);

		env->drawStart = env->resY / 2 - env->lineHeight / 2;
	  	if(env->drawStart < 0)
			env->drawStart = 0;
	  	env->drawEnd = (env->lineHeight / 2) + (env->resY / 2);
	  	if(env->drawEnd >= env->resY)
		  	env->drawEnd = env->resY - 1;

			
		// printf("start : %d, end : %d ", env->drawStart, env->drawEnd);
		draw_column(env);
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}