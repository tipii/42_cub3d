/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 16:57:41 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		init_checks(t_checks *c)
{
	c->found_res = 0;
	c->found_map = 0;
	c->found_player = 0;
	c->found_sprite = 0;
	c->found_textn = 0;
	c->found_texts = 0;
	c->found_texte = 0;
	c->found_textw = 0;
	c->found_floor = 0;
	c->found_ceiling = 0;
	c->line = malloc(sizeof(*c->line));
	c->i = 0;
	c->j = 0;
	c->k = 0;
}

void		init_map(int width, int height, t_env *env)
{
	int i;

	i = 0;
	env->map = (char **)malloc(sizeof(*env->map) * (height + 1));
	while (i < height)
	{
		env->map[i] = (char *)malloc(sizeof(char) * (width + 1));
		env->map[i][width] = 0;
		i++;
	}
	env->map[height] = 0;
	env->malloc_map = 1;
}

void		init_sprite(int i, t_env *env)
{
	int j;

	j = 0;
	if (!(env->sprites = malloc(sizeof(*env->sprites) * (i + 1))))
		error("Malloc of **sprites has failed", env);
	if (!(env->s_order = malloc(sizeof(int) * i)))
		error("Malloc of *s_order has failed", env);
	if (!(env->sprite_distance = malloc(sizeof(double) * i)))
		error("Malloc of *sprite_distance has failed", env);
	while (j < i)
	{
		if (!(env->sprites[j] = malloc(sizeof(t_sprite))))
			exit(1);
		env->sprites[j]->bpp = 0;
		env->sprites[j]->size_line = 0;
		env->sprites[j]->endian = 0;
		env->sprites[j]->width = 0;
		env->sprites[j]->height = 0;
		j++;
	}
	env->sprites[j] = 0;
	env->malloc_sprites = 1;
}
