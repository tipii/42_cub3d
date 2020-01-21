/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:31:17 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_checks(t_checks *c)
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

void	init_env(t_env *env)
{
	int		i;

	i = 0;
	env->malloc_check = 0;
	env->malloc_map = 0;
	env->malloc_sprites = 0;
	env->malloc_textures = 0;
	env->malloc_textures_ceiling = 0;
	env->malloc_textures_floor = 0;
	if(!(env->text = malloc(sizeof(*env->text) * 4)))
		error("Malloc has failed", env);
	while (i < 4)
	{
		if(!(env->text[i] = malloc(sizeof(t_text))))
			error("Malloc has failed", env);
		i++;
	}
	env->malloc_textures = 1;
	if(!(env->textf = malloc(sizeof(t_text))))
		error("Malloc has failed", env);
	env->malloc_textures_floor = 1;
	if(!(env->textc = malloc(sizeof(t_text))))
		error("Malloc has failed", env);
	env->malloc_textures_ceiling = 1;
	if(!(env->c = malloc(sizeof(t_checks))))
		error("Malloc has failed", env);
	env->malloc_check = 1;
	env->posx = 0;
	env->posy = 0;
	env->dirx = 0;
	env->diry = -1;
	env->r_speed = 0.1;
	env->t_speed = 0.1;
	env->resx = 0;
	env->resy = 0;
	env->mapwidth = 0;
	env->mapheight = 0;
	env->mapx = 1;
	env->mapy = 1;
	env->planex = 0.66;
	env->planey = 0;
	env->x = 0;
	env->y = 0;
	env->camerax = 0;
	env->raydirx = 0;
	env->raydiry = 0;
	env->sidedistx = 0;
	env->sidedisty = 0;
	env->deltadistx = 0;
	env->deltadisty = 0;
	env->perpwalldist = 0;
	env->stepx = 0;
	env->stepy = 0;
	env->hit = 0;
	env->side = 0;
	env->countsprite = 0;
	env->isprite = 0;
	env->jsprite = 0;
	env->zbuffer = NULL;
	env->bpp = 0;
	env->size_line = 0;
	env->endian = 0;
	env->mlx = NULL;
	env->window = NULL;
	env->img = NULL;
	env->img_data = NULL;
	env->lumvalue = 1;
	env->lum = 1;
	env->lineheight = 0;
	env->drawstart = 0;
	env->drawend = 0;
	env->mlx = mlx_init();
	env->current_floorx = 0;
	env->current_floory = 0;
	env->ceil_textx = 0;
	env->ceil_texty = 0;
	env->rotate_left = 0;
	env->rotate_right = 0;
	env->move_up = 0;
	env->move_down = 0;
	env->move_left = 0;
	env->move_right = 0;
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


void	init_sprite(int i, t_env *env)
{
	int j;

	j = 0;
	if (!(env->sprites = malloc(sizeof(*env->sprites) * (i + 1))))
		error("Malloc of **sprites has failed", env);
	if (!(env->s_order = malloc(sizeof(int) * i)))
		error("Malloc of *s_order has failed", env);
	if (!(env->sprite_distance = malloc(sizeof(double) * i)))
		error("Malloc of *sprite_distance has failed", env);
	while(j < i)
	{
		if(!(env->sprites[j] = malloc(sizeof(t_sprite))))
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
