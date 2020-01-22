/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:37:26 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 16:59:56 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		is_charset(char c)
{
	int		i;
	char	*charset;

	i = 0;
	charset = "012NSEW ";
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
