/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:52:00 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 16:56:41 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		print_floor(t_env *env)
{
	if (env->has_text_floor)
		put_pxl_clr(env->x, env->y, get_pxl_clr_value(env->floor_textx,
			env->floor_texty, env->textf), env);
	else
		put_pxl_clr(env->x, env->y, env->color_floor, env);
	if (env->has_text_ceiling)
		put_pxl_clr(env->x, env->resy - env->y - 1,
			get_pxl_clr_value(env->ceil_textx, env->ceil_texty,
				env->textc), env);
	else
		put_pxl_clr(env->x, env->resy - env->y - 1,
			env->color_ceiling, env);
}

void		load_and_print_floor(t_env *env)
{
	env->y = env->drawend + 1;
	while (env->y < env->resy)
	{
		env->current_dist = env->resy / (2.0 * env->y - env->resy);
		env->weight = (env->current_dist - env->dist_player) /
			(env->dist_wall - env->dist_player);
		env->current_floorx = env->weight * env->floorx_wall +
			(1.0 - env->weight) * env->posx;
		env->current_floory = env->weight * env->floory_wall +
			(1.0 - env->weight) * env->posy;
		env->ceil_textx = (int)(env->current_floorx * env->textc->width)
			% env->textc->width;
		env->ceil_texty = (int)(env->current_floory * env->textc->height)
			% env->textc->height;
		env->floor_textx = (int)(env->current_floorx * env->textf->width)
			% env->textf->width;
		env->floor_texty = (int)(env->current_floory * env->textf->height)
			% env->textf->height;
		print_floor(env);
		env->y++;
	}
}

void		draw_floor(t_env *env)
{
	if (env->side == 0)
	{
		env->floorx_wall = env->mapx;
		env->floory_wall = env->mapy + env->wallx;
	}
	else if (env->side == 2)
	{
		env->floorx_wall = env->mapx + 1.0;
		env->floory_wall = env->mapy + env->wallx;
	}
	else if (env->side == 1)
	{
		env->floorx_wall = env->mapx + env->wallx;
		env->floory_wall = env->mapy;
	}
	else
	{
		env->floorx_wall = env->mapx + env->wallx;
		env->floory_wall = env->mapy + 1.0;
	}
	env->dist_wall = env->perpwalldist;
	env->dist_player = 0.0;
	if (env->drawend < 0)
		env->drawend = env->resy;
	load_and_print_floor(env);
}
