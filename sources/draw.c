/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:19:05 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			generate_color(int r, int g, int b)
{
	int		color;
	char	*clr;

	clr = (char*)&color;
	clr[0] = b;
	clr[1] = g;
	clr[2] = r;
	return (color);
}

int			get_pxl_clr_value(int x, int y, t_text *text)
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

int			get_pxl_sprite_value(int x, int y, t_sprite *text)
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

void		put_pxl_clr(int x, int y, unsigned int color, t_env *env)
{
	char	*clr;

	clr = (char*)&color;
	env->img_data[(y * env->resx * 4) + x * 4 + 0] = clr[0];
	env->img_data[(y * env->resx * 4) + x * 4 + 1] = clr[1];
	env->img_data[(y * env->resx * 4) + x * 4 + 2] = clr[2];
	env->img_data[(y * env->resx * 4) + x * 4 + 3] = 0;
}
