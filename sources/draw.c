/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/28 13:32:36 by tpalhol          ###   ########.fr       */
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


void	get_lum_value(t_env *env)
{
	if (env->lum == 0)
	{
		env->lumvalue = 1.0;
		return ;
	}
	if (env->perpWallDist >= 0.0 && env->lumvalue < 3.0)
		env->lumvalue = 1.0;
	if (env->perpWallDist >= 3.0 && env->perpWallDist <= 5.0)
		env->lumvalue = 1.0 - (env->perpWallDist - 3.0) * 0.5;
	if (env->perpWallDist > 5.0)
		env->lumvalue = 0.0;
}

void	draw_column(t_env *env)
{
	// exit(0);
	// printf("start : %d, end : %d\n", env->drawStart, env->drawEnd);
	// exit(0);
	int i;
	int r,g,b;
	get_lum_value(env);
	if(env->side == 0)
	{
		r = 255 * env->lumvalue;
		g = 128 * env->lumvalue;
		b = 100 * env->lumvalue; 
	}
	else
	{
		r = 100 * env->lumvalue;
		g = 128 * env->lumvalue;
		b = 255 * env->lumvalue;
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