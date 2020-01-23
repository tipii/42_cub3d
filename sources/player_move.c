/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:01:25 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 16:43:52 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	move_forward(t_env *env)
{
	if (is_charset(env->map[(int)env->posy]
	[(int)(env->posx + env->dirx * env->t_speed)], "04"))
		env->posx += env->dirx * env->t_speed;
	if (is_charset(env->map[(int)(env->posy + env->diry * env->t_speed)]
	[(int)env->posx], "04"))
		env->posy += env->diry * env->t_speed;
}

void	move_backward(t_env *env)
{
	if (is_charset(env->map[(int)env->posy]
	[(int)(env->posx - env->dirx * env->t_speed)], "04"))
		env->posx -= env->dirx * env->t_speed;
	if (is_charset(env->map[(int)(env->posy - env->diry * env->t_speed)]
	[(int)env->posx], "04"))
		env->posy -= env->diry * env->t_speed;
}

void	move_left(t_env *env)
{
	if (is_charset(env->map[(int)env->posy]
	[(int)(env->posx - env->planex * env->t_speed)], "04"))
		env->posx -= env->planex * env->t_speed;
	if (is_charset(env->map[(int)(env->posy - env->planey * env->t_speed)]
	[(int)env->posx], "04"))
		env->posy -= env->planey * env->t_speed;
}

void	move_right(t_env *env)
{
	if (is_charset(env->map[(int)env->posy]
	[(int)(env->posx + env->planex * env->t_speed)], "04"))
		env->posx += env->planex * env->t_speed;
	if (is_charset(env->map[(int)(env->posy + env->planey * env->t_speed)]
	[(int)env->posx], "04"))
		env->posy += env->planey * env->t_speed;
}
