/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/26 19:58:28 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_player *init_player()
{
	t_player *player;

	if(!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->pos_x = START_POSX;
	player->pos_y = START_POSY;
	return (player);
}

t_env *init_env()
{
	t_env	*env;
	int res_x = 1920;
	int res_y = 720;

	float dps = (res_x/2) / tan((FOV / 2 * 3.14)/180);
	if(!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->fov = FOV;
	env->h_wall = H_WALL;
	env->h_player = H_PLAYER;
	env->res_x = res_x;
	env->res_y = res_y;
	env->map = NULL;
	env->dist_player_screen = dps;
	return (env);
}

