/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:37:26 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:52:52 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			is_charset(char c, char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

void		check_args_number(int nbr, int expected, t_env *env)
{
	if (nbr > expected)
		error("A definition has too many args", env);
	if (nbr < expected)
		error("A definition has not enough args", env);
}

void		has_found_all(t_env *env)
{
	t_checks	*c;

	c = env->c;
	if (!c->found_res || !c->found_player || !c->found_map ||
	!c->found_texts || !c->found_textn || !c->found_textw || !c->found_texte ||
	!c->found_sprite || !c->found_ceiling || !c->found_floor)
		error("Map error - An argument is missing", env);
}
