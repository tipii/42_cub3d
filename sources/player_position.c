/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:38:47 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 14:38:07 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	rotate_left(t_env *env)
{
	env->oldDirX = env->dirX;
	env->dirX = env->dirX * cos(-env->r_speed) - env->dirY * sin(-env->r_speed);
	env->dirY = env->oldDirX * sin(-env->r_speed) + env->dirY * cos(-env->r_speed);
	env->oldPlaneX = env->planeX;
	env->planeX = env->planeX * cos(-env->r_speed) - env->planeY * sin(-env->r_speed);
	env->planeY = env->oldPlaneX * sin(-env->r_speed) + env->planeY * cos(-env->r_speed);

}

void	rotate_right(t_env *env)
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
	if(env->map[(int)env->posY][(int)(env->posX + env->dirX * env->t_speed)] == '0') 
		env->posX += env->dirX * env->t_speed;
	if(env->map[(int)(env->posY + env->dirY * env->t_speed)][(int)env->posX] == '0') 
		env->posY += env->dirY * env->t_speed;
}
    //move backwards if no wall behind you
void	move_backward(t_env *env)
{
	if(env->map[(int)env->posY][(int)(env->posX - env->dirX * env->t_speed)] == '0')
		env->posX -= env->dirX * env->t_speed;
	if(env->map[(int)(env->posY - env->dirY * env->t_speed)][(int)env->posX] == '0')
		env->posY -= env->dirY * env->t_speed;
}

void	move_left(t_env *env)
{
	if(env->map[(int)env->posY][(int)(env->posX + env->dirY * env->t_speed)] == '0') 
		env->posX += env->dirY * env->t_speed;
	if(env->map[(int)(env->posY + env->dirX * env->t_speed)][(int)env->posX] == '0') 
		env->posY += env->dirX * env->t_speed;
}

void	move_right(t_env *env)
{
	printf("x %f, y %f \n", env->dirX, env->dirY);
	if(env->map[(int)env->posY][(int)(env->posX - env->dirY * env->t_speed)] == '0') 
		env->posX -= env->dirY * env->t_speed;
	if(env->map[(int)(env->posY - env->dirX * env->t_speed)][(int)env->posX] == '0') 
		env->posY -= env->dirX * env->t_speed;
}

int	calc_player_pos(t_env *env)
{
	if (env->rotate_left)
		rotate_left(env);
	else if (env->rotate_right)
		rotate_right(env);
	else if (env->move_up)
		move_forward(env);
	else if (env->move_down)
		move_backward(env);
	else if (env->move_left)
		move_left(env);
	else if (env->move_right)
		move_right(env);
	render(env);
	return (0);
}