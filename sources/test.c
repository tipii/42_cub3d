/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:39:43 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/26 19:50:18 by tpalhol          ###   ########.fr       */
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


// int	main()
// {
// 	t_player	*player;
// 	int			**map;

// 	if(!(player = init_player()))
// 		return (0);
// 	printf("x : %f, y : %f\n", player->pos_x, player->pos_y);

// 	printf("\n---------\n\n");
// 	if(!(map = init_map(5, 5)))
// 		return (0);
// 	show_map(map, 5,5);
// 	return (0);
// }

int main()
{
	void *mlx;
	void *window;
	int bpp, size_line, endian;
	void *img = NULL;
	char *img_data = NULL;
	unsigned int test;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 1000, 1000, "Test string");

	img = mlx_new_image (mlx, 1000, 1000);
	img_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	printf("bpp : %d, size_line : %d, endian : %d \n", bpp, size_line, endian);
	test = generate_color(255, 165, 32);

	for (size_t i = 0; i < 1000; i++)
	{
		img_data[500 * 4000 + (i * 4)] = (char)0;
		img_data[500 * 4000 + (i * 4) + 1] = (char)255;
		img_data[500 * 4000 + (i * 4) + 2] = (char)128;
		img_data[500 * 4000 + (i * 4) + 3] = (char)100;
	}

	// float len = (1920/2) / tan((FOV / 2 * 3.14)/180);
	// printf("%f\n", len);
	mlx_put_image_to_window(mlx, window, img, 0, 0);
	// exit(0);
	mlx_loop(mlx);
	return (0);
}