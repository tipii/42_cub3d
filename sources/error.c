/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:36:01 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 17:26:45 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	try_filepath(char *filepath, t_env *env)
{
	int	fd;

	fd = open(filepath, O_DIRECTORY);
	if (fd != -1)
		error("A filepath is a directory", env);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		error("A filepath is wrong", env);
}

void	try_filepath_map(char *filepath, t_env *env)
{
	int	fd;

	fd = open(filepath, O_DIRECTORY);
	if (fd != -1)
		error("Map filepath is a directory", env);
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		error("Map does not exist", env);
}

void	free_env_suite(t_env *env)
{
	int i;

	i = -1;
	if (env->malloc_sprites)
	{
		while (env->sprites[++i])
			free(env->sprites[i]);
		free(env->sprites);
	}
}

void	free_env(t_env *env)
{
	int i;

	i = -1;
	if (env->malloc_check)
	{
		if (env->malloc_line)
			free(env->c->line);
		free(env->c);
	}
	if (env->malloc_textures_floor)
		free(env->textf);
	if (env->malloc_textures_ceiling)
		free(env->textc);
	if (env->malloc_map)
	{
		while (env->map[++i])
			free(env->map[i]);
		free(env->map);
	}
	free_env_suite(env);
}

void	error(char *message, t_env *env)
{
	write(1, "Error\n", 6);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	if (env)
	{
		free_env(env);
		free(env);
	}
	exit(1);
}
