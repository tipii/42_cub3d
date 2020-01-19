/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 16:33:03 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error(char* message)
{
	write(1, "Error\n", 6);
	write(1, message, ft_strlen(message));
	write(1, "\n" ,1);
	exit(1);
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
	if(!(line = malloc(sizeof(*line))))
		error("Malloc of line has failed");
	fd = open(filepath, O_RDONLY);
	while(get_next_line(fd, line) > 0)
	{
		if(*line[0] >= '0' && *line[0] <= '9')
		{
			while ((*line)[i])
			{
				if((*line)[i] != ' ' && i % 2 == 0)
					width++;
				if ((*line)[i] == '2')
					env->countsprite++;
				i++;
			}
			if (env->mapWidth != 0 && width != 0 && width != env->mapWidth)
				error("Map is not correctly define");
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

void load_sprite(char *filepath, t_sprite *text, t_env *env)
{
	text->ptr = mlx_xpm_file_to_image(env->mlx, filepath, &text->width, &text->height);
	text->data = mlx_get_data_addr(text->ptr, &text->bpp, &text->size_line, &text->endian);
}

void	has_found_all(t_checks *c)
{
	if	(!c->found_res || !c->found_player || !c->found_map ||
	!c->found_textS || !c->found_textN || !c->found_textW || !c->found_textE ||
	!c->found_sprite || !c->found_ceiling || !c->found_floor)
		error("Map error - An argument is missing");
}

int parse(char *filepath, t_env *env)
{
	t_checks *c;
	
	if(!(c = malloc(sizeof(t_checks))))
		error("Malloc of checks has failed");
	init_checks(c);
	first_pass(filepath, env);
	init_map(env->mapWidth, env->mapHeight, env);
	init_sprite(env->countsprite, env);
	c->line = malloc(sizeof(*c->line));
	c->fd = open(filepath, O_RDONLY);
	while(get_next_line(c->fd, c->line) > 0)
	{
		c->args = ft_split(*c->line, ' ');
		if (c->args[0][0] >= '0' && c->args[0][0] <= '9')
		{
			c->found_map = 1;
			while (c->args[c->i])
			{
				if(c->args[c->i][0] == 'N' || c->args[c->i][0] == 'S'
				|| c->args[c->i][0] == 'W' || c->args[c->i][0] == 'E')
				{
					env->posX = c->k + 0.5;
					env->posY = c->j + 0.5;
					env->mapX = c->k;
					env->mapY = c->j;
					set_player_value(c->args[c->i][0], env);
					env->map[c->j][c->k++] = '0';
					c->found_player = 1;
				}
				else if (c->args[c->i][0] == '2')
				{
					env->sprites[env->isprite]->posx = c->k;
					env->sprites[env->isprite]->posy = c->j;
					env->isprite++;
					env->map[c->j][c->k++] = c->args[c->i][0];
				}
				else
					env->map[c->j][c->k++] = c->args[c->i][0];
				c->i++;
			}
			c->k = 0;
			c->j++;
		}
		else
		{
			if (ft_strcmp(c->args[0], "R") == 0)
			{
				if (ft_tablen(c->args) != 3)
					error("Wrong number of args for RES\n");
				env->resX = ft_atoi(c->args[1]);
				if (env->resX > 2560)
					env->resX = 2560;
				env->resY = ft_atoi(c->args[2]);
				if (env->resY > 1440)
					env->resY = 1440;
				if(!(env->zbuffer = malloc(sizeof(double) * env->resX)))
					error("Malloc of zbuf has failed");
				c->found_res = 1;
			}
			else if (ft_strcmp(c->args[0], "NO") == 0)
			{
				load_texture(c->args[1], env->textN, env);
				c->found_textN = 1;
			}
			else if (ft_strcmp(c->args[0], "SO") == 0)
			{
				load_texture(c->args[1], env->textS, env);
				c->found_textS = 1;
			}
			else if (ft_strcmp(c->args[0], "WE") == 0)
			{
				load_texture(c->args[1], env->textW, env);
				c->found_textW = 1;
			}
			else if (ft_strcmp(c->args[0], "EA") == 0)
			{
				load_texture(c->args[1], env->textE, env);
				c->found_textE = 1;
			}
			else if (ft_strcmp(c->args[0], "S") == 0)
			{
				while (env->jsprite < env->countsprite)
				{
					load_sprite(c->args[1], env->sprites[env->jsprite], env);
					env->jsprite++;;
				}
				c->found_sprite = 1;
			}
			else if (ft_strcmp(c->args[0], "F") == 0)
			{
				c->found_floor = 1;
			}
			else if (ft_strcmp(c->args[0], "C") == 0)
			{
				c->found_ceiling = 1;
			}
		}
		ft_freetab(c->args);
		c->i = 0;
		free(*c->line);
	}
	has_found_all(c);
	free(c);
	env->textF->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/floor.xpm", &env->textF->width, &env->textF->height);
	env->textF->data = mlx_get_data_addr(env->textF->ptr, &env->textF->bpp, &env->textF->size_line, &env->textF->endian);
	env->textC->ptr = mlx_xpm_file_to_image(env->mlx, "./textures/ceiling.xpm", &env->textC->width, &env->textC->height);
	env->textC->data = mlx_get_data_addr(env->textC->ptr, &env->textC->bpp, &env->textC->size_line, &env->textC->endian);
	close(c->fd);
	return (1);
}