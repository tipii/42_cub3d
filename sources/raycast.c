/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 09:10:49 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 09:49:11 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raytrace(t_env *env, t_player *player)
{
	env->x = 0;
	while(env->x < env->resX)
	{
		env->cameraX = (2 * env->x) / (double)env->resX - 1;
		printf("%f", env->cameraX);
		if (env->rayDirX < 0)
		{
			env->stepX = -1;
			env->sideDistX = (player->posX - env->mapX) * env->deltaDistX;
		}
		else
		{
			env->stepX = 1;
			env->sideDistX = (env->mapX + 1.0 - player->posX) * env->deltaDistX;
		}
		if (env->rayDirY < 0)
		{
			env->stepY = -1;
			env->sideDistY = (player->posY - env->mapY) * env->deltaDistY;
		}
		else
		{
			env->stepY = 1;
			env->sideDistY = (env->mapY + 1.0 - player->posY) * env->deltaDistY;
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
			if (env->map[env->mapX][env->mapY] > 0) env->hit = 1;
		}
		if (env->side == 0)
			env->perpWallDist = (env->mapX - player->posX + (1 - env->stepX) / 2) / env->rayDirX;
	  	else
			env->perpWallDist = (env->mapY - player->posY + (1 - env->stepY) / 2) / env->rayDirY;

		env->lineHeight = (int)(env->resY / env->perpWallDist);

		env->drawStart = -env->lineHeight / 2 + env->resY / 2;
	  	if(env->drawStart < 0)
			env->drawStart = 0;
	  	env->drawEnd = env->lineHeight / 2 + env->resY / 2;
	  	if(env->drawEnd >= env->resY)
		  	env->drawEnd = env->resY - 1;

		// draw_vert_line(env);
		
		env->x++;
	}
}