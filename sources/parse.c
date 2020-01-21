/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 19:19:18 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	first_pass(char *filepath, t_env *env)
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
		error("Malloc of line has failed", env);
	fd = open(filepath, O_RDONLY);
	while(get_next_line(fd, line) > 0)
	{
		if(*line[0] >= '0' && *line[0] <= '9')
		{
			while ((*line)[i])
			{
				if(!is_charset((*line)[i]))
					error("A char in map is not in charset", env);
				if((*line)[i] != ' ' && i % 2 == 0)
					width++;
				if ((*line)[i] == '2')
					env->countsprite++;
				i++;
			}
			if (env->mapwidth != 0 && width != 0 && width != env->mapwidth)
				error("Map has various size of lines", env);
			env->mapwidth = width;
			height++;
		}
		width = 0;
		i = 0;
		free(*line);
	}
	env->mapheight = height;
	close(fd);
}

void	has_found_all(t_env *env)
{
	t_checks	*c;

	c = env->c;
	printf("%d %d %d %d %d %d %d %d %d %d", c->found_res, c->found_player, c->found_map, c->found_texts, c->found_textn, c->found_textw, c->found_texte , c->found_sprite, c->found_ceiling, c->found_floor);
	if	(!c->found_res || !c->found_player || !c->found_map ||
	!c->found_texts || !c->found_textn || !c->found_textw || !c->found_texte ||
	!c->found_sprite || !c->found_ceiling || !c->found_floor)
		error("Map error - An argument is missing", env);
}

void	found_player(t_env *env, t_checks *c)
{
	if (c->found_player)
		error("More than one player position is define in the map", env);
	env->posx = c->i + 0.5;
	env->posy = c->j + 0.5;
	env->mapx = c->i;
	env->mapy = c->j;
	set_player_value(c->args[c->i][0], env);
	env->map[c->j][c->i] = '0';
	c->found_player = 1;
}

void	found_sprite(t_env *env, t_checks *c)
{
	env->sprites[env->isprite]->spos_x = c->i;
	env->sprites[env->isprite]->spos_y = c->j;
	env->isprite++;
	env->map[c->j][c->i] = c->args[c->i][0];
}

void	add_line_to_map(t_env *env, t_checks *c)
{
	c->i = 0;
	while (c->args[c->i])
	{
		if(c->args[c->i][0] == 'N' || c->args[c->i][0] == 'S'
		|| c->args[c->i][0] == 'W' || c->args[c->i][0] == 'E')
			found_player(env, c);
		else if (c->args[c->i][0] == '2')
			found_sprite(env, c);
		else
		{
			env->map[c->j][c->i] = c->args[c->i][0];
		}
		// printf("%d %d \n", c->i, c->j);		
		c->i++;
	}
	c->j++;
}

void	parse_map(t_env *env, t_checks *c)
{
	if(c->found_map)
		error("Map not in one block or not last argument", env);
	c->found_map = 1;

	c->args = ft_split(*c->line, ' ');
	add_line_to_map(env, c);
	ft_freetab(c->args);

	while(get_next_line(c->fd, c->line) > 0 && (*c->line[0] >= '0' && *c->line[0] <= '9'))
	{
		// printf("%s\n", *c->line);
		c->args = ft_split(*c->line, ' ');
		add_line_to_map(env, c);
		ft_freetab(c->args);
	}

}

void	check_map_is_close(t_env *env)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (k < env->mapheight)
	{
		if (k == 0 || k == env->mapheight - 1)
		{
			while(env->map[k][i])
			{
				if(env->map[k][i] != '1')
					error("Map is not closed", env);
				i++;
			}
			i = 0;
		}
		else
		{
			if(env->map[k][0] != '1' || env->map[k][env->mapwidth -1] != '1')
					error("Map is not closed", env);
		}
		k++;
	}
	
}

void second_pass(char *filepath, t_env *env)
{
	t_checks *c;
	c = env->c;
	c->fd = open(filepath, O_RDONLY);
	while((get_next_line(c->fd, c->line)) > 0)
	{
		if (*c->line[0] >= '0' && *c->line[0] <= '9')
		{
			parse_map(env, c);
			check_map_is_close(env);
		}
		else
		{
			c->args = ft_split(*c->line, ' ');
			if (ft_strcmp(c->args[0], "R") == 0)
			{
				if (ft_tablen(c->args) != 3)
					error("Wrong number of args for RES", env);
				env->resx = ft_atoi(c->args[1]);
				if (env->resx > 2560)
					env->resx = 2560;
				env->resy = ft_atoi(c->args[2]);
				if (env->resy > 1440)
					env->resy = 1440;
				if(!(env->zbuffer = malloc(sizeof(double) * env->resx)))
					error("Malloc of zbuf has failed", env);
				c->found_res = 1;
			}
			else if (ft_strcmp(c->args[0], "NO") == 0)
			{
				try_filepath(c->args[1], env);
				load_texture(c->args[1], env->text[3], env);
				c->found_textn = 1;
			}
			else if (ft_strcmp(c->args[0], "SO") == 0)
			{
				try_filepath(c->args[1], env);
				load_texture(c->args[1], env->text[1], env);
				c->found_texts = 1;
			}
			else if (ft_strcmp(c->args[0], "WE") == 0)
			{
				try_filepath(c->args[1], env);
				load_texture(c->args[1], env->text[2], env);
				c->found_textw = 1;
			}
			else if (ft_strcmp(c->args[0], "EA") == 0)
			{
				try_filepath(c->args[1], env);
				load_texture(c->args[1], env->text[0], env);
				c->found_texte = 1;
			}
			else if (ft_strcmp(c->args[0], "S") == 0)
			{
				try_filepath(c->args[1], env);
				while (env->jsprite < env->countsprite)
				{
					load_sprite(c->args[1], env->sprites[env->jsprite], env);
					env->jsprite++;;
				}
				c->found_sprite = 1;
			}
			else if (ft_strcmp(c->args[0], "F") == 0)
			{
				load_floor_or_ceil(c->args[0], c->args[1], env);
				c->found_floor = 1;
			}
			else if (ft_strcmp(c->args[0], "C") == 0)
			{
				load_floor_or_ceil(c->args[0], c->args[1], env);
				c->found_ceiling = 1;
			}
			ft_freetab(c->args);
		}
		free(*c->line);
	}
	close(c->fd);
}

int parse(char *filepath, t_env *env)
{
	try_filepath_map(filepath, env);
	first_pass(filepath, env);
	init_map(env->mapwidth, env->mapheight, env);
	init_sprite(env->countsprite, env);
	second_pass(filepath, env);
	has_found_all(env);
	return (1);
}