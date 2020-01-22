/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:31:20 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 16:37:02 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		is_in_range(int c)
{
	if (c >= 0 && c <= 255)
		return (1);
	return (0);
}

int		is_rgb(char *arg, t_env *env)
{
	char	**args;
	int		r;
	int		g;
	int		b;

	args = ft_split(arg, ",");
	if (ft_tablen(args) == 3)
	{
		r = ft_atoi(args[0]);
		g = ft_atoi(args[1]);
		b = ft_atoi(args[2]);
		if (!(is_in_range(r) && is_in_range(g) && is_in_range(b)))
			error("An rgb value is invalid", env);
		ft_freetab(args);
		return (generate_color(r, g, b));
	}
	else
	{
		ft_freetab(args);
		return (-1);
	}
}
