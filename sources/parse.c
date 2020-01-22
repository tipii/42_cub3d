/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:55:17 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		first_pass(char *filepath, t_env *env)
{
	int		fd;
	char	**line;
	int		i;
	int		height;
	int		width;

	i = 0;
	width = 0;
	height = 0;
	if (!(line = malloc(sizeof(*line))))
		error("Malloc of line has failed", env);
	fd = open(filepath, O_RDONLY);
	while (get_next_line(fd, line) > 0)
	{
		if (*line[0] >= '0' && *line[0] <= '9')
		{
			while ((*line)[i])
			{
				if (!is_charset((*line)[i], "012NSEW "))
					error("A char in map is not in charset", env);
				if ((*line)[i] != ' ' && i % 2 == 0)
					width++;
				if ((*line)[i] == '2')
					env->countsprite++;
				i++;
			}
			if (env->mapwidth != 0 && width != 0 && width != env->mapwidth)
				error("Map has various size of lines", env);
			env->mapwidth = width;
			height++;
		}
		width = 0;
		i = 0;
		free(*line);
	}
	env->mapheight = height;
	close(fd);
}

void		look_for_elem(t_env *env, t_checks *c)
{
	if (c->args[0] && !is_charset(c->args[0][0], "RNSWEFCR"))
		error("An unknown element is define", env);
	if (ft_strcmp(c->args[0], "R") == 0)
		found_res(env, c);
	else if (ft_strcmp(c->args[0], "NO") == 0)
		found_textn(env, c);
	else if (ft_strcmp(c->args[0], "SO") == 0)
		found_texts(env, c);
	else if (ft_strcmp(c->args[0], "WE") == 0)
		found_textw(env, c);
	else if (ft_strcmp(c->args[0], "EA") == 0)
		found_texte(env, c);
	else if (ft_strcmp(c->args[0], "S") == 0)
		found_textsprites(env, c);
	else if (ft_strcmp(c->args[0], "F") == 0)
		found_floor(env, c);
	else if (ft_strcmp(c->args[0], "C") == 0)
		found_ceiling(env, c);
}

void		second_pass(char *filepath, t_env *env)
{
	t_checks *c;

	c = env->c;
	c->fd = open(filepath, O_RDONLY);
	while ((get_next_line(c->fd, c->line)) > 0)
	{
		if (*c->line[0] >= '0' && *c->line[0] <= '9')
		{
			parse_map(env, c);
			check_map_is_close(env);
		}
		else
		{
			c->args = ft_split(*c->line, " \t");
			look_for_elem(env, c);
			ft_freetab(c->args);
		}
		free(*c->line);
	}
	close(c->fd);
}

int			parse(char *filepath, t_env *env)
{
	try_filepath_map(filepath, env);
	first_pass(filepath, env);
	init_map(env->mapwidth, env->mapheight, env);
	init_sprite(env->countsprite, env);
	second_pass(filepath, env);
	has_found_all(env);
	return (1);
}
