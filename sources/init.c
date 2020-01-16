/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/16 17:34:16 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_checks	*init_checks()
{
	t_checks *checks;

	if(!(checks = malloc(sizeof(t_checks))))
		error("Malloc of checks has failed");
	checks->found_res = 0;
	checks->found_map = 0;
	checks->found_player = 0;
	checks->found_sprite = 0;
	checks->found_textN = 0;
	checks->found_textS = 0;
	checks->found_textE = 0;
	checks->found_textW = 0;
	checks->found_floor = 0;
	checks->found_ceiling = 0;
	checks->line = malloc(sizeof(*checks->line));
	checks->i = 0;
	checks->j = 0;
	checks->k = 0;
	return (checks);
}

t_env *init_env()
{
	t_env	*env;

	if(!(env = malloc(sizeof(t_env))))
		return (NULL);	
	if(!(env->textS = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textN = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textE = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textW = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textF = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textC = malloc(sizeof(t_text))))
		return (NULL);
	if(!(env->textsprite = malloc(sizeof(t_text))))
		return (NULL);
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
	env->rayDirX0 = 0;
	env->rayDirY0 = 0;
	env->rayDirX1 = 0;
	env->rayDirY1 = 0;
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

	env->textS->width = 0;
	env->textS->height = 0;


	return (env);
}


char	**init_map(int width, int height)
{
	char **map;
	int i;
	
	i = 0;
	map = (char **)malloc(sizeof(*map) * (height + 1));
	while (i < height)
	{
		map[i] = (char *)malloc(sizeof(char) * (width + 1));
		map[i][width] = 0;
		i++;
	}
	map[height] = 0;
	return (map);
}


t_sprite **init_sprite(int i, t_env *env)
{
	int j;
	t_sprite **sprites;

	j = 0;	
	printf("%d sprites\n", i);
	if (!(sprites = malloc(sizeof(*sprites) * (i + 1))))
		error("Malloc of **sprites has failed");
	if (!(env->s_order = malloc(sizeof(int) * i)))
		error("Malloc of *s_order has failed");
	if (!(env->sprite_distance = malloc(sizeof(double) * i)))
		error("Malloc of *sprite_distance has failed");
	while(j < i)
	{
		if(!(sprites[j] = malloc(sizeof(t_sprite))))
			exit(1);
		sprites[j]->bpp = 0;
		sprites[j]->size_line = 0;
		sprites[j]->endian = 0;
		sprites[j]->width = 0;
		sprites[j]->height = 0;
		j++;
	}
	sprites[j] = 0;
	return (sprites);
}
// void		init_all(t_env *env, t_env *env)
// {
// 	env = init_env();

// 	env = init_env(env);
// 	printf("%d", env->resX);
// }