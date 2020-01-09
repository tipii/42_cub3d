/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/09 16:36:50 by tpalhol          ###   ########.fr       */
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
			if (env->map[env->mapY][env->mapX] > '0')
				env->hit = 1;
		}
		if (env->side == 0 || env->side == 2)
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



		// Texture Start
		double wallX; //where exactly the wall was hit
	  	if (env->side == 0 || env->side == 2) 
			wallX = env->posY + env->perpWallDist * env->rayDirY;
	  	else
			wallX = env->posX + env->perpWallDist * env->rayDirX;
	  	wallX -= floor((wallX));
	  	//x coordinate on the texture
	  	int texX = (int)(wallX * (double)env->textS->width);
		// printf("%d  ", texX);

	  	if((env->side == 0 || env->side == 2) && env->rayDirX > 0) 
			texX = env->textS->width - texX - 1;
	  	if((env->side == 1 || env->side == 3) && env->rayDirY < 0)
			texX = env->textS->width - texX - 1;

		double step = 1.0 * env->textS->height / env->lineHeight;
      	// Starting texture coordinate
      	double texPos = (env->drawStart - env->resY / 2 + env->resY / 2) * step;
      	for(int y = env->drawStart; y < env->drawEnd; y++)
      	{
        	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        	int texY = (int)texPos & (env->textS->height - 1);
			printf("x : %d , y : %d \n", texX, texY);
        	texPos += step;
        	put_pxl_clr(env->x, y, get_pxl_clr_value(texX, texY, env->textS), env) ;
        	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
      	}



		// printf("start : %d, end : %d ", env->drawStart, env->drawEnd);
		// draw_column(env);
		env->x++;
	}
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}