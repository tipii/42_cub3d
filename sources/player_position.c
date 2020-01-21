/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:38:47 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 15:18:51 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_left(t_env *env)
{
	env->oldDirX = env->dirX;
	env->dirX = env->dirX * cos(-env->r_speed);
	env->dirX -= env->dirY * sin(-env->r_speed);
	env->dirY = env->dirY * cos(-env->r_speed);
	env->dirY += env->oldDirX * sin(-env->r_speed);
	env->oldPlaneX = env->planeX;
	env->planeX = env->planeX * cos(-env->r_speed);
	env->planeX -= env->planeY * sin(-env->r_speed);
	env->planeY = env->planeY * cos(-env->r_speed);
	env->planeY += env->oldPlaneX * sin(-env->r_speed);
}

void	rotate_right(t_env *env)
{
	env->oldDirX = env->dirX;
	env->dirX = env->dirX * cos(env->r_speed);
	env->dirX -= env->dirY * sin(env->r_speed);
	env->dirY = env->dirY * cos(env->r_speed);
	env->dirY += env->oldDirX * sin(env->r_speed);
	env->oldPlaneX = env->planeX;
	env->planeX = env->planeX * cos(env->r_speed);
	env->planeX -= env->planeY * sin(env->r_speed);
	env->planeY = env->planeY * cos(env->r_speed);
	env->planeY += env->oldPlaneX * sin(env->r_speed);
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
