/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 15:44:17 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	**init_map(int width, int height)
{
	int **map;
	int i;
	
	i = 0;
	map = (int **)malloc(sizeof(*map) * width);
	while (i < width)
	{
		map[i] = (int *)malloc(sizeof(int) * height);
		i++;
	}

	/* MAP GENERATION */
	int x = 0;
	int y = 0;
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
	map[2][5] = 1;
	map[4][2] = 1;
	map[9][7] = 1;
	/*END OF MAP GENERATION*/

	return (map);
}