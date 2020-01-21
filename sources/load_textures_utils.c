/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:31:20 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 15:31:41 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		is_rgb(char *arg)
{
	char	**args;
	int		r;
	int		g;
	int		b;

	args = ft_split(arg, ',');
	if (ft_tablen(args) == 3)
	{
		r = ft_atoi(args[0]);
		g = ft_atoi(args[1]);
		b = ft_atoi(args[2]);
		ft_freetab(args);
		return (generate_color(r, g, b));
	}
	else
	{
		ft_freetab(args);
		return (-1);
	}
}
