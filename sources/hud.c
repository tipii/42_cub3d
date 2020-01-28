/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:36:25 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/28 13:56:19 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_hud(t_env *env)
{
	try_filepath("./textures/hud/hud.xpm", env);
	load_texture("./textures/hud/hud.xpm", env->texthud, env);
}

void print_hud(t_env *env)
{
	int		x;
	int		y;
	double	ratio_w;
	double	ratio_h;
	int color;
	x = 0;
	y = 0;
	ratio_w = (double)env->texthud->width / (double)env->resx;
	ratio_h = (double)env->texthud->height / (double)env->resy;
	while (x < env->resx)
	{
		while(y < env->resy)
		{
			color = get_pxl_clr_value((int)(x * ratio_w), (int)(y * ratio_h), env->texthud);
			if (color)
				put_pxl_clr(x, y, color, env);
			y++;
		}
		x++;
		y = 0;
	}
}	