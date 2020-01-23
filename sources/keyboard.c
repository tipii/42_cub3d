/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:47:16 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 15:59:06 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	return (0);
}
