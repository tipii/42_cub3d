/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:37:44 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:27:56 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_player_north(t_env *env)
{
	env->dirx = 0;
	env->diry = -1;
	env->planex = 0.66;
	env->planey = 0;
}

void	set_player_south(t_env *env)
{
	env->dirx = 0;
	env->diry = 1;
	env->planex = -0.66;
	env->planey = 0;
}

void	set_player_east(t_env *env)
{
	env->dirx = 1;
	env->diry = 0;
	env->planex = 0;
	env->planey = 0.66;
}

void	set_player_west(t_env *env)
{
	env->dirx = -1;
	env->diry = 0;
	env->planex = 0;
	env->planey = -0.66;
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
