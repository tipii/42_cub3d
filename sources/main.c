/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:39:43 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 14:19:48 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

// void			loop(t_env *env)
// {
// }

// MAIN TEST //
int				main()
{
	t_env		*env;

	if(!(env = malloc(sizeof(t_env))))
		error("Malloc has failed", env);	
	init_env(env);
	parse("./maps/map_1.cub", env);

	//to delete
	printf("\n\x1b[33mParsing...\x1b[39m\n\n");
	printf("MAP : Width : %d, Height : %d \n", env->mapWidth, env->mapHeight);
	printf("PLAYER : Pos x %f, Pos y %f\n", env->posX, env->posY);
	printf("\n\x1b[33mInitializing...\x1b[39m\n\n");
	printf("RES : x %d, y %d\n", env->resX, env->resY);
	//
	env->window = mlx_new_window(env->mlx, env->resX, env->resY,
		"AWESOME RAYCASTING SHIT V0.0000001beta");
	env->img = mlx_new_image (env->mlx, env->resX, env->resY);
	env->img_data = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
		&env->endian);

	//to delete
	printf("MLX INFOS : bpp : %d, size_line : %d, endian : %d \n\n", env->bpp,
		env->size_line, env->endian);
	show_map(env);
	//
	mlx_hook(env->window, 2, 1L << 0, hook_keydown, env);
	mlx_hook(env->window, 3, 1L << 1, hook_keyup, env);
	render(env);
	mlx_loop_hook(env->mlx, calc_player_pos, env);
	mlx_loop(env->mlx);
	// loop(env);
	return (0);
}

