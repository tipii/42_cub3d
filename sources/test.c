/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:39:43 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/22 19:48:30 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void show_map(int **map, int width, int height)
{
	int x = 0;
	int y = 0;

	while (y < height)
	{
		while (x < width)
		{
			printf("%d ", map[x][y]);
			x++;
		}
		printf("\n");
		y++;
		x = 0;
	}
}


int	main()
{
	t_player	*player;
	int			**map;

	if(!(player = init_player()))
		return (0);
	printf("x : %f, y : %f\n", player->pos_x, player->pos_y);

	printf("\n---------\n\n");
	if(!(map = init_map(5, 5)))
		return (0);
	show_map(map, 5,5);
	return (0);
}