/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 16:30:05 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 15:56:32 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	sort_sprite(t_env *env)
{
	int j;
	int i;
	int tmp;

	i = 0;
	j = 0; 

	while (i < (env->countsprite - 1))
	{
		while (j < env->countsprite - 1 - i)
		{
			if(env->sprite_distance[j] < env->sprite_distance[j+1])
			{
				tmp = env->s_order[j+1];
				env->s_order[j+1] = env->s_order[j];
				env->s_order[j] = tmp;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	sprite_casting(t_env *env)
{
	int i;

	i = 0;
	while (i < env->countsprite)
	{
		env->s_order[i] = i;
		env->sprite_distance[i] = pow((env->posX - env->sprites[i]->posx), 2);
		env->sprite_distance[i] += pow((env->posY - env->sprites[i]->posy), 2);
		i++;
	}
	sort_sprite(env);
	i = 0;
	while (i < env->countsprite)
	{
		env->spritex = env->sprites[env->s_order[i]]->posx - env->posX + 0.5;
		env->spritey = env->sprites[env->s_order[i]]->posy - env->posY + 0.5;
		env->invdet = 1.0 / (env->planeX * env->dirY - env->dirX * env->planeY);
		env->transformx = env->dirY * env->spritex - env->dirX * env->spritey;
		env->transformx *= env->invdet;
		env->transformy = -env->planeY * env->spritex + env->planeX * env->spritey;
		env->transformy *= env->invdet;
		env->spritescreenx = (int)((env->resX / 2) * (1 + env->transformx / env->transformy));
		env->spriteheight = abs((int)(env->resY / (env->transformy)));
		env->drawstarty = -env->spriteheight / 2 + env->resY / 2;
		if (env->drawstarty < 0)
			env->drawstarty = 0;
		env->drawendy = env->spriteheight / 2 + env->resY / 2;
		if (env->drawendy >= env->resY)
			env->drawendy = env->resY - 1;
		env->spritewidth = abs((int)(env->resY / (env->transformy)));
		env->drawstartx = -env->spritewidth / 2 + env->spritescreenx;
		if (env->drawstartx < 0)
			env->drawstartx = 0;
		env->drawendx = env->spritewidth / 2 + env->spritescreenx;
		if (env->drawendx >= env->resX)
			env->drawendx = env->resX - 1;
		env->stripe = env->drawstartx;
		while (env->stripe < env->drawendx)
		{
			env->texX = (int)(256 * (env->stripe - (-env->spritewidth / 2 + env->spritescreenx)) * env->sprites[i]->width / env->spritewidth) / 256;
			if (env->transformy > 0 && env->stripe > 0 &&
			env->stripe < env->resX && env->transformy < env->zbuffer[env->stripe])
			{
				env->y = env->drawstarty;
				while (env->y < env->drawendy)
				{
					env->d = (env->y) * 256 - env->resY * 128 + env->spriteheight * 128;
					env->texY = ((env->d * env->sprites[i]->height) / env->spriteheight) / 256;
					env->color = get_pxl_sprite_value(env->texX, env->texY, env->sprites[i]);
					if (env->color)
						put_pxl_clr(env->stripe, env->y, env->color, env);
					env->y++;
				}
			}
			env->stripe++;
		}
		i++;
	}
}
