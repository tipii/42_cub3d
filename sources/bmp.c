/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:24:06 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/27 15:40:33 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_bmp(t_bmp *bmp, int width, int height)
{
	bmp->bpp = 3;
	bmp->header_size = 14;
	bmp->info_header_size = 40;
	bmp->padding[0] = 0;
	bmp->padding[1] = 0;
	bmp->padding[2] = 0;
	bmp->padding_size = (4 - (width * bmp->bpp) % 4) % 4;
	bmp->file_size = bmp->header_size + bmp->info_header_size +
		(bmp->bpp * width + bmp->padding_size) * height;
}

void	bmp_create_file_header(t_bmp *bmp)
{
	int i;

	i = 0;
	while (i < 14)
	{
		bmp->file_header[i] = 0;
		i++;
	}
	bmp->file_header[0] = (unsigned char)('B');
	bmp->file_header[1] = (unsigned char)('M');
	bmp->file_header[2] = (unsigned char)(bmp->file_size);
	bmp->file_header[3] = (unsigned char)(bmp->file_size >> 8);
	bmp->file_header[4] = (unsigned char)(bmp->file_size >> 16);
	bmp->file_header[5] = (unsigned char)(bmp->file_size >> 24);
	bmp->file_header[10] = (unsigned char)(bmp->header_size +
		bmp->info_header_size);
}

void	bmp_create_info_header(t_bmp *bmp, int width, int height)
{
	int i;

	i = 0;
	while (i < 40)
	{
		bmp->info_header[i] = 0;
		i++;
	}
	bmp->info_header[0] = (unsigned char)(bmp->info_header_size);
	bmp->info_header[4] = (unsigned char)(width);
	bmp->info_header[5] = (unsigned char)(width >> 8);
	bmp->info_header[6] = (unsigned char)(width >> 16);
	bmp->info_header[7] = (unsigned char)(width >> 24);
	bmp->info_header[8] = (unsigned char)(height);
	bmp->info_header[9] = (unsigned char)(height >> 8);
	bmp->info_header[10] = (unsigned char)(height >> 16);
	bmp->info_header[11] = (unsigned char)(height >> 24);
	bmp->info_header[12] = (unsigned char)(1);
	bmp->info_header[14] = (unsigned char)(bmp->bpp * 8);
}

void	bmp_write_image(t_bmp *bmp, t_env *env)
{
	int y;
	int x;

	write(bmp->fd, bmp->file_header, 14);
	write(bmp->fd, bmp->info_header, 40);
	y = env->resy - 1;
	x = 0;
	while (y >= 0)
	{
		while (x < env->resx)
		{
			write(bmp->fd, &env->img_data[(y * env->size_line) + x * 4], 3);
			x++;
		}
		x = 0;
		y--;
	}
}

int		bmp_generate(t_env *env, char *filename)
{
	t_bmp	*bmp;

	if (!(bmp = malloc(sizeof(t_bmp))))
		return (0);
	init_bmp(bmp, env->resx, env->resy);
	bmp_create_file_header(bmp);
	bmp_create_info_header(bmp, env->resx, env->resy);
	bmp->fd = open(filename, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	bmp_write_image(bmp, env);
	close(bmp->fd);
	free(bmp);
	return (1);
}
