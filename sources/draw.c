/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:51:33 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/26 17:54:49 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int generate_color(int r, int g, int b)
{
	int		color;
	char	*clr;

	clr = (char*)&color;
	clr[0] = g;
	clr[1] = b;
	clr[2] = r;

	// printf("%d\n", color);
	return (color);
}