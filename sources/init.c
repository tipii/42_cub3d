/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/28 00:33:11 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_env *init_env()
{
	t_env	*env;
	int res_x = 720;
	int res_y = 576;
	float pos_X = 5;
	float pos_Y = 5;

	if(!(env = malloc(sizeof(t_env))))
		return (NULL);

	env->posX = pos_X;
	env->posY = pos_Y;
	env->dirX = -1;
	env->dirY = 0;
	env->r_speed = 0.1;
	env->t_speed = 0.1;
	env->resX = res_x;
	env->resY = res_y;
	env->fov = FOV;
	if (!(env->map = init_map(10, 10)))
		return(NULL);
	env->mapX = (int)pos_X;
	env->mapY = (int)pos_Y;
	env->planeX = 0;
	env->planeY = 0.66;
	env->oldPlaneX = 0;
	env->oldPlaneY = 0;
	env->x = 0;
	env->cameraX = 0;
	env->rayDirX = 0;
	env->rayDirY = 0;
	env->sideDistX = 0;
	env->sideDistY = 0;
	env->deltaDistX = 0;
	env->deltaDistY = 0;
	env->perpWallDist = 0;
	env->stepX = 0;
	env->stepY = 0;
	env->hit = 0;
	env->side = 0;
	env->bpp = 0;
	env->size_line = 0;
	env->endian = 0;
	env->mlx = NULL;
	env->window = NULL;
	env->img = NULL;
	env->img_data = NULL;
	env->lumvalue = 1;
	env->lineHeight = 0;
	env->drawStart = 0;
	env->drawEnd = 0;


	return (env);
}

// void		init_all(t_env *env, t_env *env)
// {
// 	env = init_env();

// 	env = init_env(env);
// 	printf("%d", env->resX);
// }