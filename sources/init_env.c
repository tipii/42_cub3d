/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:57:19 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/23 17:01:40 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		init_env_4(t_env *env)
{
	env->ceil_textx = 0;
	env->ceil_texty = 0;
	env->rotate_left = 0;
	env->rotate_right = 0;
	env->move_up = 0;
	env->move_down = 0;
	env->move_left = 0;
	env->move_right = 0;
	env->fp_i = 0;
	env->fp_width = 0;
	env->fp_height = 0;
}

void		init_env_3(t_env *env)
{
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
}

void		init_env_2(t_env *env)
{
	env->finish_map = 0;
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
}

void		init_env_start(t_env *env)
{
	env->malloc_check = 0;
	env->malloc_line = 0;
	env->malloc_map = 0;
	env->malloc_sprites = 0;
	env->malloc_textures = 0;
	env->malloc_textures_ceiling = 0;
	env->malloc_textures_floor = 0;
	env->malloc_line = 1;
	env->malloc_check = 1;
}

void		init_env(t_env *env)
{
	int		i;

	i = 0;
	init_env_start(env);
	if (!(env->text = malloc(sizeof(*env->text) * 4)))
		error("Malloc of texture array has failed", env);
	while (i < 4)
	{
		if (!(env->text[i] = malloc(sizeof(t_text))))
			error("Malloc of a texture has failed", env);
		i++;
	}
	env->malloc_textures = 1;
	if (!(env->textf = malloc(sizeof(t_text))))
		error("Malloc of textf failed", env);
	env->malloc_textures_floor = 1;
	if (!(env->textc = malloc(sizeof(t_text))))
		error("Malloc of textc failed", env);
	env->malloc_textures_ceiling = 1;
	if (!(env->c = malloc(sizeof(t_checks))))
		error("Malloc has failed", env);
	init_checks(env->c);
	init_env_2(env);
	init_env_3(env);
	init_env_4(env);
}
