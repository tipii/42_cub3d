/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:39:43 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 16:45:04 by tpalhol          ###   ########.fr       */
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

void			show_map(t_env *env)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("\x1b[33mMap...\x1b[39m\n\n");
	while (env->map[y])
	{
		while (env->map[y][x])
		{
			printf("%c ", env->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
		x = 0;
	}
	printf("\n");
}

void			init_mlx(t_env *env)
{
	env->window = mlx_new_window(env->mlx, env->resx, env->resy,
		"AWESOME RAYCASTING SHIT V0.0000001beta");
	env->img = mlx_new_image(env->mlx, env->resx, env->resy);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
		&env->endian);
}

int				main(int argc, char **argv)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	if (!(env = malloc(sizeof(t_env))))
		error("Malloc has failed", env);
	init_env(env);
	parse("./maps/map_1.cub", env);
	printf("\n\x1b[33mParsing...\x1b[39m\n\n");
	printf("MAP : Width : %d, Height : %d \n", env->mapwidth, env->mapheight);
	printf("PLAYER : Pos x %f, Pos y %f\n", env->posx, env->posy);
	printf("\n\x1b[33mInitializing...\x1b[39m\n\n");
	printf("RES : x %d, y %d\n", env->resx, env->resy);
	show_map(env);
	init_mlx(env);
	mlx_hook(env->window, 17, 1L << 0, quit_program, env);
	mlx_hook(env->window, 2, 1L << 0, hook_keydown, env);
	mlx_hook(env->window, 3, 1L << 1, hook_keyup, env);
	render(env);
	mlx_loop_hook(env->mlx, calc_player_pos, env);
	mlx_loop(env->mlx);
	return (0);
}
