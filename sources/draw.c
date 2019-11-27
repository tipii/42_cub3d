/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 15:59:07 by tpalhol          ###   ########.fr       */
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

void	draw_column(t_env *env)
{
	// exit(0);
	// printf("start : %d, end : %d\n", env->drawStart, env->drawEnd);
	// exit(0);
	int i;
	int r,g,b;
	if(env->side == 0)
	{
		r = 255;
		g = 128;
		b = 100; 
	}
	else
	{
		r = 100;
		g = 128;
		b = 255;
	}
	
	i = env->drawStart;
	while (i < env->drawEnd)
	{
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 0] = (char)b;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 1] = (char)g;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 2] = (char)r;
		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 3] = (char)0;
		i++;
	}
}