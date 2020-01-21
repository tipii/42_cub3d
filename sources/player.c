/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:37:44 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 15:39:26 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_player_north(t_env *env)
{
	env->dirX = 0;
	env->dirY = -1;
	env->planeX = 0.66;
	env->planeY = 0;
}

void	set_player_south(t_env *env)
{
	env->dirX = 0;
	env->dirY = 1;
	env->planeX = -0.66;
	env->planeY = 0;
}

void	set_player_east(t_env *env)
{
	env->dirX = 1;
	env->dirY = 0;
	env->planeX = 0;
	env->planeY = 0.66;
}

void	set_player_west(t_env *env)
{
	env->dirX = -1;
	env->dirY = 0;
	env->planeX = 0;
	env->planeY = -0.66;
}

void	set_player_value(char c, t_env *env)
{
	if (c == 'N')
		set_player_north(env);
	if (c == 'S')
		set_player_south(env);
	if (c == 'E')
		set_player_east(env);
	if (c == 'W')
		set_player_west(env);
}
