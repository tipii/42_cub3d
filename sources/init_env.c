/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 19:11:08 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/22 19:43:12 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	**init_map(int width, int height)
{
	int **map;
	int i;
	int x;
	int y;
	
	i = 0;
	map = (int **)malloc(sizeof(*map) * width);
	while (i < width)
	{
		map[i] = (int *)malloc(sizeof(int) * height);
		i++;
	}

	
	x = 0;
	y = 0;

	while(x < width)
	{
		while(y < height)
		{
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
				map[x][y] = 1;
			else
				map[x][y] = 0;
			y++;
		}
		y = 0;
		x++;
	}
	
	map[2][1] = 1;
	return (map);
}