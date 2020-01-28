/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:57:52 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/28 19:30:53 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		check_map_is_close(t_env *env)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (k < env->mapheight)
	{
		if (k == 0 || k == env->mapheight - 1)
		{
			while (env->map[k][i])
			{
				if (env->map[k][i] != '1')
					error("Map is not closed", env);
				i++;
			}
			i = 0;
		}
		else
		{
			if (env->map[k][0] != '1' || env->map[k][env->mapwidth - 1] != '1')
				error("Map is not closed", env);
		}
		k++;
	}
}

void		format_line(t_checks *c)
{
	int	i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 1;
	while ((*c->line)[i])
	{
		if ((*c->line)[i] == ' ')
		{
			while ((*c->line)[i + k] && (*c->line)[i + k] == ' ')
				k++;
			j = i;
			while ((*c->line)[j + k])
			{
				(*c->line)[j] = (*c->line)[j + k];
				(*c->line)[j + k] = 0;
				j++;
			}
		}
		k = 1;
		i++;
	}
}

void		parse_map(t_env *env, t_checks *c)
{
	if (c->found_map)
		error("Map not in one block or not last argument", env);
	c->found_map = 1;
	format_line(c);
	add_line_to_map(env, c);
	free(*c->line);
	while (get_next_line(c->fd, c->line) > 0 &&
		(*c->line[0] >= '0' && *c->line[0] <= '9'))
	{
		format_line(c);
		add_line_to_map(env, c);
		free(*c->line);
	}
}

void		add_line_to_map(t_env *env, t_checks *c)
{
	c->i = 0;
	while ((*c->line)[c->i])
	{
		if ((*c->line)[c->i] == 'N' || (*c->line)[c->i] == 'S'
		|| (*c->line)[c->i] == 'W' || (*c->line)[c->i] == 'E')
			found_player(env, c);
		else if ((*c->line)[c->i] == '2')
			found_sprite(env, c);
		else
			env->map[c->j][c->i] = (*c->line)[c->i];
		c->i++;
	}
	c->j++;
}
