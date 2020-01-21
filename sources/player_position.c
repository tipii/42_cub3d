/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:38:47 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:46:46 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_left(t_env *env)
{
	env->olddirx = env->dirx;
	env->dirx = env->dirx * cos(-env->r_speed);
	env->dirx -= env->diry * sin(-env->r_speed);
	env->diry = env->diry * cos(-env->r_speed);
	env->diry += env->olddirx * sin(-env->r_speed);
	env->oldplanex = env->planex;
	env->planex = env->planex * cos(-env->r_speed);
	env->planex -= env->planey * sin(-env->r_speed);
	env->planey = env->planey * cos(-env->r_speed);
	env->planey += env->oldplanex * sin(-env->r_speed);
}

void	rotate_right(t_env *env)
{
	env->olddirx = env->dirx;
	env->dirx = env->dirx * cos(env->r_speed);
	env->dirx -= env->diry * sin(env->r_speed);
	env->diry = env->diry * cos(env->r_speed);
	env->diry += env->olddirx * sin(env->r_speed);
	env->oldplanex = env->planex;
	env->planex = env->planex * cos(env->r_speed);
	env->planex -= env->planey * sin(env->r_speed);
	env->planey = env->planey * cos(env->r_speed);
	env->planey += env->oldplanex * sin(env->r_speed);
}

int		calc_player_pos(t_env *env)
{
	if (env->rotate_left)
		rotate_left(env);
	if (env->rotate_right)
		rotate_right(env);
	if (env->move_left)
		move_left(env);
	if (env->move_right)
		move_right(env);
	if (env->move_up)
		move_forward(env);
	if (env->move_down)
		move_backward(env);
	render(env);
	return (0);
}
