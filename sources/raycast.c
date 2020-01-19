/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 19:52:58 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void try_floor(t_env *env)
{
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

      //4 different wall directions possible
    if(env->side == 0)
    {
    	floorXWall = env->mapX;
        floorYWall = env->mapY + env->wallX;
    }
    else if(env->side == 2)
    {
        floorXWall = env->mapX + 1.0;
        floorYWall = env->mapY + env->wallX;
    }
    else if(env->side == 1)
    {
        floorXWall = env->mapX + env->wallX;
        floorYWall = env->mapY;
    }
    else
    {
        floorXWall = env->mapX + env->wallX;
        floorYWall = env->mapY + 1.0;
    }

      double distWall, distPlayer, currentDist;

      distWall = env->perpWallDist;
      distPlayer = 0.0;

      if (env->drawEnd < 0)
	  	env->drawEnd = env->resY; //becomes < 0 when the integer overflows

      //draw the floor from drawEnd to the bottom of the screen
      for(env->y = env->drawEnd; env->y < env->resY; env->y++)
      {
        currentDist = env->resY / (2.0 * env->y - env->resY); //you could make a small lookup table for this instead

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * env->posX;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * env->posY;

        int floorTexX, floorTexY, ceilingTextX, ceilingTextY;
		ceilingTextX = (int)(currentFloorX * env->textC->width) % env->textC->width;
		ceilingTextY = (int)(currentFloorY * env->textC->height) % env->textC->height;
        floorTexX = (int)(currentFloorX * env->textF->width) % env->textF->width;
        floorTexY = (int)(currentFloorY * env->textF->height) % env->textF->height;

		put_pxl_clr(env->x, env->y, get_pxl_clr_value(floorTexX, floorTexY, env->textF), env);
		put_pxl_clr(env->x, env->resY - env->y - 1, get_pxl_clr_value(ceilingTextX, ceilingTextY, env->textC), env);
      }
}
// void	floor_print(t_env *env)
// {
// 	env->cellX = (int)env->floorX;
// 	env->cellY = (int)env->floorY;
// 	env->tx = (int)(env->textN->width * (env->floorX - env->cellX)) & (env->textN->width - 1);
// 	env->ty = (int)(env->textN->height * (env->floorY - env->cellY)) & (env->textN->height - 1);
// 	env->floorX += env->floorStepX;
// 	env->floorY += env->floorStepY;
// 	put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->tx, env->ty, env->textF), env);
// 	put_pxl_clr(env->x, env->resY - env->y - 1, get_pxl_clr_value(env->tx, env->ty, env->textC), env);
// 	env->x++;
// }

// void	floor_casting(t_env *env)
// {
// 	while (env->y < env->resY)
// 	{
// 		env->rayDirX0 = env->dirX - env->planeX;
// 		env->rayDirY0 = env->dirY - env->planeY;
// 		env->rayDirX1 = env->dirX + env->planeX;
// 		env->rayDirY1 = env->dirY + env->planeY;
// 		env->p = env->y - env->resY / 2;
// 		env->posZ = 0.5 * env->resY;
// 		env->rowDistance = env->posZ / env->p; 
// 		env->floorStepX = env->rowDistance * (env->rayDirX1 - env->rayDirX0) / env->resX;
// 		env->floorStepY = env->rowDistance * (env->rayDirY1 - env->rayDirY0) / env->resX;
// 		env->floorX = env->posX + env->rowDistance * env->rayDirX0;
//     	env->floorY = env->posY + env->rowDistance * env->rayDirY0;
// 		while (env->x < env->resX)
// 		{
// 			floor_print(env);
// 		}
// 		env->x = 0;
// 		env->y++;
// 	}
// 	env->x = 0;
// 	env->y = 0;
// }

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
	//Check if ray has hit a wall
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
	env->texX = (int)(env->wallX * (double)env->text[env->side]->width);

	if((env->side == 0 || env->side == 2) && env->rayDirX > 0) 
		env->texX = env->text[env->side]->width - env->texX - 1;
	if((env->side == 1 || env->side == 3) && env->rayDirY < 0)
		env->texX = env->text[env->side]->width - env->texX - 1;

	env->step = 1.0 * env->text[env->side]->height / env->lineHeight;
	env->texPos = (env->drawStart - env->resY / 2 + env->lineHeight / 2) * env->step;
}

// void	draw_walls(t_env *env)
// {

//  }

void	render(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, env->resX, env->resY);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line, &env->endian);
	env->x = 0;
	env->y = 0;
	//FLOOR CASTING
	// floor_casting(env);
	//WALL CASTING
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
        	put_pxl_clr(env->x, env->y, get_pxl_clr_value(-env->texX, env->texY, env->text[env->side]), env);
			env->y++;
      	}
		try_floor(env);
		env->zbuffer[env->x] = env->perpWallDist;
		env->y = 0;
		env->x++;
	}
	sprite_casting(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img, 0, 0);
}
