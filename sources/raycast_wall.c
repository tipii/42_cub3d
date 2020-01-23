/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:53:42 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 13:44:10 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		load_draw_values(t_env *env)
{
	env->lineheight = (int)(env->resy / env->perpwalldist);
	env->drawstart = env->resy / 2 - env->lineheight / 2;
	if (env->drawstart < 0)
		env->drawstart = 0;
	env->drawend = (env->lineheight / 2) + (env->resy / 2);
	if (env->drawend >= env->resy)
		env->drawend = env->resy - 1;
	if (env->side == 0 || env->side == 2)
		env->wallx = env->posy + env->perpwalldist * env->raydiry;
	else
		env->wallx = env->posx + env->perpwalldist * env->raydirx;
	env->wallx -= floor(env->wallx);
	env->texx = (int)(env->wallx * (double)env->text[env->side]->width);
	if ((env->side == 0 || env->side == 2) && env->raydirx > 0)
		env->texx = env->text[env->side]->width - env->texx - 1;
	if ((env->side == 1 || env->side == 3) && env->raydiry < 0)
		env->texx = env->text[env->side]->width - env->texx - 1;
	env->step = 1.0 * env->text[env->side]->height / env->lineheight;
	env->texpos = (env->drawstart - env->resy / 2 + env->lineheight / 2)
		* env->step;
}

void		draw_wall(t_env *env)
{
	env->y = env->drawstart;
	while (env->y < env->drawend)
	{
		env->texy = (int)env->texpos;
		env->texpos += env->step;
		put_pxl_clr(env->x, env->y,
			get_pxl_clr_value(env->text[env->side]->width - env->texx,
				env->texy, env->text[env->side]), env);
		env->y++;
	}
}
