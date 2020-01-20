/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/20 17:16:24 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_checks(t_checks *c)
{
	c->found_res = 0;
	c->found_map = 0;
	c->found_player = 0;
	c->found_sprite = 0;
	c->found_textN = 0;
	c->found_textS = 0;
	c->found_textE = 0;
	c->found_textW = 0;
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
	if(!(env->textF = malloc(sizeof(t_text))))
		error("Malloc has failed", env);
	env->malloc_textures_floor = 1;
	if(!(env->textC = malloc(sizeof(t_text))))
		error("Malloc has failed", env);
	env->malloc_textures_ceiling = 1;
	if(!(env->c = malloc(sizeof(t_checks))))
		error("Malloc has failed", env);
	env->malloc_check = 1;
	env->posX = 0;
	env->posY = 0;
	env->dirX = 0;
	env->dirY = -1;
	env->r_speed = 0.1;
	env->t_speed = 0.1;
	env->resX = 0;
	env->resY = 0;
	env->fov = FOV;
	env->mapWidth = 0;
	env->mapHeight = 0;
	env->mapX = 1;
	env->mapY = 1;
	env->planeX = 0.66;
	env->planeY = 0;
	env->oldPlaneX = 0;
	env->oldPlaneY = 0;
	env->x = 0;
	env->y = 0;
	env->cameraX = 0;
	env->rayDirX = 0;
	env->rayDirY = 0;
	env->sideDistX = 0;
	env->sideDistY = 0;
	env->deltaDistX = 0;
	env->deltaDistY = 0;
	env->perpWallDist = 0;
	env->stepX = 0;
	env->stepY = 0;
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
	env->lineHeight = 0;
	env->drawStart = 0;
	env->drawEnd = 0;
	env->mlx = mlx_init();
	env->current_floorx = 0;
	env->current_floory = 0;
	env->ceil_textx = 0;
	env->ceil_texty = 0;
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
