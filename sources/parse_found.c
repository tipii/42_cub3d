/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_found.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:00:50 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:04:23 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		has_found_all(t_env *env)
{
	t_checks	*c;

	c = env->c;
	if (!c->found_res || !c->found_player || !c->found_map ||
	!c->found_texts || !c->found_textn || !c->found_textw || !c->found_texte ||
	!c->found_sprite || !c->found_ceiling || !c->found_floor)
		error("Map error - An argument is missing", env);
}

void		found_player(t_env *env, t_checks *c)
{
	if (c->found_player)
		error("More than one player position is define in the map", env);
	env->posx = c->i + 0.5;
	env->posy = c->j + 0.5;
	env->mapx = c->i;
	env->mapy = c->j;
	set_player_value(c->args[c->i][0], env);
	env->map[c->j][c->i] = '0';
	c->found_player = 1;
}

void		found_sprite(t_env *env, t_checks *c)
{
	env->sprites[env->isprite]->spos_x = c->i;
	env->sprites[env->isprite]->spos_y = c->j;
	env->isprite++;
	env->map[c->j][c->i] = c->args[c->i][0];
}

void		found_res(t_env *env, t_checks *c)
{
	if (c->found_res)
		error("Resolution is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 3, env);
	env->resx = ft_atoi(c->args[1]);
	env->resy = ft_atoi(c->args[2]);
	if (env->resy <= 0 || env->resx <= 0)
		error("Resolution should be positive and > 0", env);
	if (env->resx > 2560)
		env->resx = 2560;
	if (env->resy > 1440)
		env->resy = 1440;
	printf("%d %d\n", env->resx, env->resy);
	if (!(env->zbuffer = malloc(sizeof(double) * env->resx)))
		error("Malloc of zbuf has failed", env);
	c->found_res = 1;
}