/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:01:25 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 15:23:14 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_env *env)
{
	if (env->map[(int)env->posY][(int)(env->posX + env->dirX * env->t_speed)]
		== '0')
		env->posX += env->dirX * env->t_speed;
	if (env->map[(int)(env->posY + env->dirY * env->t_speed)][(int)env->posX]
		== '0')
		env->posY += env->dirY * env->t_speed;
}

void	move_backward(t_env *env)
{
	if (env->map[(int)env->posY][(int)(env->posX - env->dirX * env->t_speed)]
		== '0')
		env->posX -= env->dirX * env->t_speed;
	if (env->map[(int)(env->posY - env->dirY * env->t_speed)][(int)env->posX]
		== '0')
		env->posY -= env->dirY * env->t_speed;
}

void	move_left(t_env *env)
{
	if (env->map[(int)env->posY][(int)(env->posX - env->planeX * env->t_speed)]
		== '0')
		env->posX -= env->planeX * env->t_speed;
	if (env->map[(int)(env->posY - env->planeY * env->t_speed)][(int)env->posX]
		== '0')
		env->posY -= env->planeY * env->t_speed;
}

void	move_right(t_env *env)
{
	if (env->map[(int)env->posY][(int)(env->posX + env->planeX * env->t_speed)]
		== '0')
		env->posX += env->planeX * env->t_speed;
	if (env->map[(int)(env->posY + env->planeY * env->t_speed)][(int)env->posX]
		== '0')
		env->posY += env->planeY * env->t_speed;
}
