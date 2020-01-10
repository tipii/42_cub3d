/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/10 15:29:15 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
int	first_pass(char *filepath, t_env *env)
{
	int fd;
	char **line;
	int i;
	int height;
	int width;

	i = 0;
	width = 0;
	height = 0;
	line = malloc(sizeof(*line));
	fd = open(filepath, O_RDONLY);
	while(get_next_line(fd, line) > 0)
	{
		if(*line[0] >= '0' && *line[0] <= '9')
		{
			while ((*line)[i])
			{
				if((*line)[i] != ' ')
					width++;
				i++;
				
			}
			env->mapWidth = width;
			height++;
		}
		width = 0;
		i = 0;
		free(*line);
	}
	env->mapHeight = height;
	free(line);
	close(fd);
	return (1);
}
void	set_player_value(char c, t_env *env)
{
	if (c == 'N')
	{
		env->dirX = 0;
		env->dirY = -1;
		env->planeX = 0.66;
		env->planeY = 0;
	}
	if (c == 'S')
	{
		env->dirX = 0;
		env->dirY = 1;
		env->planeX = -0.66;
		env->planeY = 0;
	}
	if (c == 'E')
	{
		env->dirX = 1;
		env->dirY = 0;
		env->planeX = 0;
		env->planeY = 0.66;
	}
	if (c == 'W')
	{
		env->dirX = -1;
		env->dirY = 0;
		env->planeX = 0;
		env->planeY = -0.66;
	}
}

int parse(char *filepath, t_env *env)
{
	int	fd;
	char **line;
	char **args;
	int i = 0;
	int j = 0;
	int k = 0;
	// t_error *error;


	first_pass(filepath, env);
	env->map = init_map(env->mapWidth, env->mapHeight);
	line = malloc(sizeof(*line));
	fd = open(filepath, O_RDONLY);
	while(get_next_line(fd, line) > 0)
	{
		if (*line[0] == 'R')
		{
			args = ft_split(*line, ' ');
			if (ft_tablen(args) != 3)
				exit(0);
			env->resX = ft_atoi(args[1]);
			env->resY = ft_atoi(args[2]);
			ft_freetab(args);
		}
		if (*line[0] >= '0' && *line[0] <= '9')
		{
			while ((*line)[i])
			{
				if((*line)[i] != ' ')
				{
					if((*line)[i] == 'N' || (*line)[i] == 'S' || (*line)[i] == 'W' || (*line)[i] == 'E')
					{
						env->posX = k + 0.5;
						env->posY = j + 0.5;
						env->mapX = k;
						env->mapY = j;
						set_player_value((*line)[i], env);
						env->map[j][k++] = '0';

					}
					else
						env->map[j][k++] = (*line)[i];
				}
				i++;
			}
			k = 0;
			j++;
		}
		i = 0;
		// free(*line);
	}

	//texture load test
	// env->textS->width = 32;
	// printf("%d", env->textS->height);
	env->textS->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/stone.xpm", &env->textS->width, &env->textS->height);
	env->textS->data = mlx_get_data_addr(env->textS->ptr, &env->textS->bpp, &env->textS->size_line, &env->textS->endian);
	env->textN->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/eagle.xpm", &env->textN->width, &env->textN->height);
	env->textN->data = mlx_get_data_addr(env->textN->ptr, &env->textN->bpp, &env->textN->size_line, &env->textN->endian);
	env->textE->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/redbrick.xpm", &env->textE->width, &env->textE->height);
	env->textE->data = mlx_get_data_addr(env->textE->ptr, &env->textE->bpp, &env->textE->size_line, &env->textE->endian);
	env->textW->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/wood.xpm", &env->textW->width, &env->textW->height);
	env->textW->data = mlx_get_data_addr(env->textW->ptr, &env->textW->bpp, &env->textW->size_line, &env->textW->endian);

	close(fd);
	return (1);
}