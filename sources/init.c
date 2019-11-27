/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 07:40:18 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_player *init_player()
{
	t_player *player;

	if(!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->posX = START_POSX;
	player->posX = START_POSY;
	return (player);
}

t_env *init_env(t_player *player)
{
	t_env	*env;
	int res_x = 720;
	int res_y = 576;

	if(!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->fov = FOV;
	env->wallH = H_WALL;
	env->playerH = H_PLAYER;
	env->resX = res_x;
	env->resY = res_y;
	if (!(env->map = init_map(10, 10)))
		return(NULL);
	env->mapX = (int)player->posX;
	env->mapY = (int)player->posY;
	return (env);
}

// void		init_all(t_player *player, t_env *env)
// {
// 	player = init_player();

// 	env = init_env(player);
// 	printf("%d", env->resX);
// }