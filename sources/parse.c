/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 18:02:50 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		first_pass_core(t_env *env)
{
	if (!is_charset((*env->fp_line)[env->fp_i], "012NSEW "))
		error("A char in map is not in charset", env);
	if ((*env->fp_line)[env->fp_i] != ' ' && env->fp_i % 2 == 0)
		env->fp_width++;
	if ((*env->fp_line)[env->fp_i] == '2')
		env->countsprite++;
	env->fp_i++;
}

void		first_pass(char *filepath, t_env *env)
{
	if (!(env->fp_line = malloc(sizeof(*env->fp_line))))
		error("Malloc of line has failed", env);
	env->fp_fd = open(filepath, O_RDONLY);
	while (get_next_line(env->fp_fd, env->fp_line) > 0)
	{
		if (*env->fp_line[0] >= '0' && *env->fp_line[0] <= '9')
		{
			while ((*env->fp_line)[env->fp_i])
				first_pass_core(env);
			if (env->mapwidth != 0 && env->fp_width != 0
				&& env->fp_width != env->mapwidth)
				error("Map has various size of lines", env);
			env->mapwidth = env->fp_width;
			env->fp_height++;
		}
		env->fp_width = 0;
		env->fp_i = 0;
		free(*env->fp_line);
	}
	free(env->fp_line);
	env->mapheight = env->fp_height;
	close(env->fp_fd);
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
