/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 09:35:21 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int generate_color(int r, int g, int b)
{
	int		color;
	char	*clr;

	clr = (char*)&color;
	clr[0] = b;
	clr[1] = g;
	clr[2] = r;

	// printf("%d\n", color);
	return (color);
}

void	draw_vert_line(t_env *env)
{
	for (int i = env->drawStart; i < env->drawEnd; i++)
	{
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 0] = (char)0;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 1] = (char)255;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 2] = (char)128;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 3] = (char)100;
	}
}