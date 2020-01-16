/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/16 16:27:14 by tpalhol          ###   ########.fr       */
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

void	sprite_casting(t_env *env)
{
	int i;

	i = 0;
	while (i < env->countsprite)
	{
		env->sprite_order[i] = i;
		env->sprite_distance[i] = ((env->posX - env->sprites[i]->posx) * (env->posX - env->sprites[i]->posx) + (env->posY - env->sprites[i]->posy) * (env->posY - env->sprites[i]->posy));
		i++;
	}
	i = 0;
	while (i < env->countsprite)
	{
		env->spritex = env->sprites[env->sprite_order[i]]->posx - env->posX + 0.5;
		env->spritey = env->sprites[env->sprite_order[i]]->posy - env->posY + 0.5;
		env->invdet = 1.0 / (env->planeX * env->dirY - env->dirX * env->planeY);
		env->transformx = env->invdet * (env->dirY * env->spritex - env->dirX * env->spritey);
    	env->transformy = env->invdet * (-env->planeY * env->spritex + env->planeX * env->spritey);
		env->spritescreenx = (int)((env->resX / 2) * (1 + env->transformx / env->transformy));
		env->spriteheight = abs((int)(env->resY / (env->transformy)));
		env->drawstarty = -env->spriteheight / 2 + env->resY / 2;
      	if(env->drawstarty < 0) 
			env->drawstarty = 0;
      	env->drawendy = env->spriteheight / 2 + env->resY / 2;
      	if(env->drawendy >= env->resY) 
			env->drawendy = env->resY - 1;
		env->spritewidth = abs((int)(env->resY / (env->transformy)));
      	env->drawstartx = -env->spritewidth / 2 + env->spritescreenx;
      	if(env->drawstartx < 0) 
		  	env->drawstartx = 0;
      	env->drawendx = env->spritewidth / 2 + env->spritescreenx;
      	if(env->drawendx >= env->resX) 
		  	env->drawendx = env->resX - 1;

		env->stripe = env->drawstartx;
		while (env->stripe < env->drawendx)
     	{
        	env->texX = (int)(256 * (env->stripe - (-env->spritewidth / 2 + env->spritescreenx)) * env->sprites[i]->width / env->spritewidth) / 256;
			if(env->transformy > 0 && env->stripe > 0 && env->stripe < env->resX && env->transformy < env->zbuffer[env->stripe])
			{
				env->y = env->drawstarty;
				while (env->y < env->drawendy) //for every pixel of the current stripe
				{
					env->d = (env->y) * 256 - env->resY * 128 + env->spriteheight * 128; //256 and 128 factors to avoid floats
					env->texY = ((env->d * env->sprites[i]->height) / env->spriteheight) / 256;
					env->color = get_pxl_sprite_value(env->texX, env->texY, env->sprites[i]);
					if(env->color)
						put_pxl_clr(env->stripe, env->y, env->color, env);
					env->y++;
				}
			}
			env->stripe++;
      	}
	  	i++;
	}
}