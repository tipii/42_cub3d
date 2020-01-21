/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:01:25 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:27:56 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_env *env)
{
	if (env->map[(int)env->posy][(int)(env->posx + env->dirx * env->t_speed)]
		== '0')
		env->posx += env->dirx * env->t_speed;
	if (env->map[(int)(env->posy + env->diry * env->t_speed)][(int)env->posx]
		== '0')
		env->posy += env->diry * env->t_speed;
}

void	move_backward(t_env *env)
{
	if (env->map[(int)env->posy][(int)(env->posx - env->dirx * env->t_speed)]
		== '0')
		env->posx -= env->dirx * env->t_speed;
	if (env->map[(int)(env->posy - env->diry * env->t_speed)][(int)env->posx]
		== '0')
		env->posy -= env->diry * env->t_speed;
}

void	move_left(t_env *env)
{
	if (env->map[(int)env->posy][(int)(env->posx - env->planex * env->t_speed)]
		== '0')
		env->posx -= env->planex * env->t_speed;
	if (env->map[(int)(env->posy - env->planey * env->t_speed)][(int)env->posx]
		== '0')
		env->posy -= env->planey * env->t_speed;
}

void	move_right(t_env *env)
{
	if (env->map[(int)env->posy][(int)(env->posx + env->planex * env->t_speed)]
		== '0')
		env->posx += env->planex * env->t_speed;
	if (env->map[(int)(env->posy + env->planey * env->t_speed)][(int)env->posx]
		== '0')
		env->posy += env->planey * env->t_speed;
}
