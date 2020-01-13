/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/13 15:00:57 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char* message)
{
	write(1, "Error\n", 6);
	write(1, message, ft_strlen(message));
	exit(0);
}

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

void load_texture(char *filepath, t_text *text, t_env *env)
{
	text->ptr = mlx_xpm_file_to_image(env->mlx, filepath, &text->width, &text->height);
	text->data = mlx_get_data_addr(text->ptr, &text->bpp, &text->size_line, &text->endian);
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
		args = ft_split(*line, ' ');
		if (args[0][0] >= '0' && args[0][0] <= '9')
		{
			while (args[i])
			{
				if(args[i][0] == 'N' || args[i][0] == 'S' || args[i][0] == 'W' || args[i][0] == 'E')
					{
						env->posX = k + 0.5;
						env->posY = j + 0.5;
						env->mapX = k;
						env->mapY = j;
						set_player_value(args[i][0], env);
						env->map[j][k++] = '0';

					}
					else
						env->map[j][k++] = args[i][0];
				
				i++;
			}
			k = 0;
			j++;
		}
		else
		{
			if (ft_strcmp(args[0], "R") == 0)
			{
				if (ft_tablen(args) != 3)
					error("Wrong number of args for RES\n");
				env->resX = ft_atoi(args[1]);
				if (env->resX > 2560)
					env->resX = 2560;
				env->resY = ft_atoi(args[2]);
				if (env->resY > 1440)
					env->resY = 1440;
			}
			else if (ft_strcmp(args[0], "NO") == 0)
				load_texture(args[1], env->textN, env);
			else if (ft_strcmp(args[0], "SO") == 0)
				load_texture(args[1], env->textS, env);
			else if (ft_strcmp(args[0], "WE") == 0)
				load_texture(args[1], env->textW, env);
			else if (ft_strcmp(args[0], "EA") == 0)
				load_texture(args[1], env->textE, env);
		}
		ft_freetab(args);
		i = 0;
		free(*line);
	}
	
	env->textF->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/floor.xpm", &env->textF->width, &env->textF->height);
	env->textF->data = mlx_get_data_addr(env->textF->ptr, &env->textF->bpp, &env->textF->size_line, &env->textF->endian);
	env->textC->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/ceiling.xpm", &env->textC->width, &env->textC->height);
	env->textC->data = mlx_get_data_addr(env->textC->ptr, &env->textC->bpp, &env->textC->size_line, &env->textC->endian);
	close(fd);
	return (1);
}