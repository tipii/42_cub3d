/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:47:16 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/28 13:32:33 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_right(t_env *env)
{
	env->oldDirX = env->dirX;
	env->dirX = env->dirX * cos(-env->r_speed) - env->dirY * sin(-env->r_speed);
	env->dirY = env->oldDirX * sin(-env->r_speed) + env->dirY * cos(-env->r_speed);
	env->oldPlaneX = env->planeX;
	env->planeX = env->planeX * cos(-env->r_speed) - env->planeY * sin(-env->r_speed);
	env->planeY = env->oldPlaneX * sin(-env->r_speed) + env->planeY * cos(-env->r_speed);

}

void	rotate_left(t_env *env)
{
	env->oldDirX = env->dirX;
	env->dirX = env->dirX * cos(env->r_speed) - env->dirY * sin(env->r_speed);
	env->dirY = env->oldDirX * sin(env->r_speed) + env->dirY * cos(env->r_speed);
	env->oldPlaneX = env->planeX;
	env->planeX = env->planeX * cos(env->r_speed) - env->planeY * sin(env->r_speed);
	env->planeY = env->oldPlaneX * sin(env->r_speed) + env->planeY * cos(env->r_speed);
}

void	move_forward(t_env *env)
{
	if(env->map[(int)(env->posX + env->dirX * env->t_speed)][(int)env->posY] == 0) 
		env->posX += env->dirX * env->t_speed;
	if(env->map[(int)env->posX][(int)(env->posY + env->dirY * env->t_speed)] == 0) 
		env->posY += env->dirY * env->t_speed;
}
    //move backwards if no wall behind you
void	move_backward(t_env *env)
{
	if(env->map[(int)(env->posX - env->dirX * env->t_speed)][(int)env->posY] == 0)
		env->posX -= env->dirX * env->t_speed;
	if(env->map[(int)env->posX][(int)(env->posY - env->dirY * env->t_speed)] == 0)
		env->posY -= env->dirY * env->t_speed;
}

void	toogle_lum(t_env *env)
{
	if (env->lum == 0)
		env->lum = 1;
	else
		env->lum = 0;
}

int		hook_keydown(int key, t_env *env)
{
	// if (key == K_ESC)
	// 	exit(EXIT_SUCCESS);
	if (key == KEY_T)
	 	toogle_lum(env);
	if (key == KEY_LEFT)
	 	rotate_left(env);
	if (key == KEY_RIGHT)
		rotate_right(env);
	if (key == KEY_UP)
		move_forward(env);
	if (key == KEY_DOWN)
		move_backward(env);
	render(env);
	return (0);
}