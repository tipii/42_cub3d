/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:39:43 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 17:29:38 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				quit_program(t_env *env)
{
	mlx_clear_window(env->mlx, env->window);
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->window);
	free_env(env);
	exit(0);
	return (0);
}

void			init_mlx(t_env *env)
{
	env->window = mlx_new_window(env->mlx, env->resx, env->resy,
		"Cub3D");
	env->img = mlx_new_image(env->mlx, env->resx, env->resy);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
		&env->endian);
}


int				main(int argc, char **argv)
{
	t_env		*env;

	env = NULL;
	if (argc < 2)
		error("You need at least one arg", env);
	else if (argc == 3 || argc == 2)
	{
		if (!(env = malloc(sizeof(t_env))))
			error("Malloc has failed", env);
		init_env(env);
		if (parse(argv[1], env))
		{
			init_mlx(env);
			mlx_hook(env->window, 17, 1L << 0, quit_program, env);
			mlx_hook(env->window, 2, 1L << 0, hook_keydown, env);
			mlx_hook(env->window, 3, 1L << 1, hook_keyup, env);
			render(env);
			mlx_loop_hook(env->mlx, calc_player_pos, env);
			mlx_loop(env->mlx);
		}
	}
	else if (argc > 3)
		error("Too many args", env);
	

	return (0);
}
