/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 19:37:26 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int generate_color(int r, int g, int b)
// {
// 	int		color;
// 	char	*clr;

// 	clr = (char*)&color;
// 	clr[0] = b;
// 	clr[1] = g;
// 	clr[2] = r;

// 	// printf("%d\n", color);
// 	return (color);
// }


// void	get_lum_value(t_env *env)
// {
// 	if (env->lum == 0)
// 	{
// 		env->lumvalue = 1.0;
// 		return ;
// 	}
// 	if (env->perpWallDist >= 0.0 && env->lumvalue < 3.0)
// 		env->lumvalue = 1.0;
// 	if (env->perpWallDist >= 3.0 && env->perpWallDist <= 5.0)
// 		env->lumvalue = 1.0 - (env->perpWallDist - 3.0) * 0.5;
// 	if (env->perpWallDist > 5.0)
// 		env->lumvalue = 0.0;
// }

int get_pxl_clr_value(int x, int y, t_text *text)
{

	int		color;
	char	*clr;
	
	clr = (char*)&color;
	clr[0] = text->data[(y * text->width * 4) + x * 4 + 0];
	clr[1] = text->data[(y * text->width * 4) + x * 4 + 1];
	clr[2] = text->data[(y * text->width * 4) + x * 4 + 2];
	clr[3] = 0;
	return (color);
}

int get_pxl_sprite_value(int x, int y, t_sprite *text)
{

	int		color;
	char	*clr;
	
	clr = (char*)&color;
	clr[0] = text->data[(y * text->size_line) + x * (text->bpp / 8) + 0];
	clr[1] = text->data[(y * text->size_line) + x * (text->bpp / 8) + 1];
	clr[2] = text->data[(y * text->size_line) + x * (text->bpp / 8) + 2];
	clr[3] = 0;
	return (color);
}

void put_pxl_clr(int x, int y, unsigned int color, t_env *env)
{
	char	*clr;
	
	clr = (char*)&color;
	env->img_data[(y * env->resX * 4) + x * 4 + 0] = clr[0];
	env->img_data[(y * env->resX * 4) + x * 4 + 1] = clr[1];
	env->img_data[(y * env->resX * 4) + x * 4 + 2] = clr[2];
	env->img_data[(y * env->resX * 4) + x * 4 + 3] = 0;
}

// void	draw_column(t_env *env)
// {
// 	// exit(0);
// 	// printf("start : %d, end : %d\n", env->drawStart, env->drawEnd);
// 	// exit(0);
// 	int i;
// 	int r,g,b;
// 	get_lum_value(env);
// 	if(env->side == 0)
// 	{
// 		r = 255 * env->lumvalue;
// 		g = 20 * env->lumvalue;
// 		b = 20 * env->lumvalue; 
// 	}
// 	else if (env->side == 1)
// 	{
// 		r = 20 * env->lumvalue;
// 		g = 255 * env->lumvalue;
// 		b = 20 * env->lumvalue;
// 	}
// 	else if (env->side == 2)
// 	{
// 		r = 20 * env->lumvalue;
// 		g = 20 * env->lumvalue;
// 		b = 255 * env->lumvalue;
// 	}	
// 	else if (env->side == 3)
// 	{
// 		r = 128 * env->lumvalue;
// 		g = 128 * env->lumvalue;
// 		b = 128 * env->lumvalue;
// 	}
	
// 	i = env->drawStart;
// 	while (i < env->drawEnd)
// 	{
// 		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 0] = (char)b;
// 		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 1] = (char)g;
// 		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 2] = (char)r;
// 		env->img_data[(i * env->size_line) + env->x * (env->bpp / 8) + 3] = (char)0;
// 		i++;
// 	}
// }