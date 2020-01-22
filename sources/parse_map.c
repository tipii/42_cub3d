/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:57:52 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:00:47 by tpalhol          ###   ########.fr       */
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

void		parse_map(t_env *env, t_checks *c)
{
	if (c->found_map)
		error("Map not in one block or not last argument", env);
	c->found_map = 1;
	c->args = ft_split(*c->line, " \t");
	add_line_to_map(env, c);
	ft_freetab(c->args);
	free(*c->line);
	while (get_next_line(c->fd, c->line) > 0 &&
		(*c->line[0] >= '0' && *c->line[0] <= '9'))
	{
		c->args = ft_split(*c->line, " \t");
		add_line_to_map(env, c);
		ft_freetab(c->args);
		free(*c->line);
	}
}

void		add_line_to_map(t_env *env, t_checks *c)
{
	c->i = 0;
	while (c->args[c->i])
	{
		if (c->args[c->i][0] == 'N' || c->args[c->i][0] == 'S'
		|| c->args[c->i][0] == 'W' || c->args[c->i][0] == 'E')
			found_player(env, c);
		else if (c->args[c->i][0] == '2')
			found_sprite(env, c);
		else
			env->map[c->j][c->i] = c->args[c->i][0];
		c->i++;
	}
	c->j++;
}
