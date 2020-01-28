/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:47:16 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/28 14:16:23 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	hook_key_h(t_env *env)
{
	if (env->print_hud)
		env->print_hud = 0;
	else
		env->print_hud = 1;
}

int		hook_keydown(int key, t_env *env)
{
	if (key == KEY_A)
		env->move_left = 1;
	else if (key == KEY_D)
		env->move_right = 1;
	else if (key == KEY_W)
		env->move_up = 1;
	else if (key == KEY_S)
		env->move_down = 1;
	else if (key == KEY_LEFT)
		env->rotate_left = 1;
	else if (key == KEY_RIGHT)
		env->rotate_right = 1;
	else if (key == KEY_H)
		hook_key_h(env);
	else if (key == 257)
	{
		env->r_speed = 0.15;
		env->t_speed = 0.15;
	}
	else if (key == KEY_ESC)
		quit_program(env);
	return (0);
}

int		hook_keyup(int key, t_env *env)
{
	if (key == KEY_A)
		env->move_left = 0;
	else if (key == KEY_D)
		env->move_right = 0;
	else if (key == KEY_W)
		env->move_up = 0;
	else if (key == KEY_S)
		env->move_down = 0;
	else if (key == KEY_LEFT)
		env->rotate_left = 0;
	else if (key == KEY_RIGHT)
		env->rotate_right = 0;
	else if (key == 257)
	{
		env->r_speed = 0.1;
		env->t_speed = 0.1;
	}
	return (0);
}
