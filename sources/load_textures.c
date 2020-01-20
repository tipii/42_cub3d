/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:42:26 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/20 18:20:47 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int		is_rgb(char *arg)
{
	char	**args;
	int		r;
	int		g;
	int		b;

	args = ft_split(arg, ',');
	if (ft_tablen(args) == 3)
	{
		r = ft_atoi(args[0]);
		g = ft_atoi(args[1]);
		b = ft_atoi(args[2]);
		ft_freetab(args);
		return (generate_color(r, g, b));
	}
	else
	{
		ft_freetab(args);
		return (-1);
	}
}

void	load_texture(char *filepath, t_text *text, t_env *env)
{
	text->ptr = mlx_xpm_file_to_image(env->mlx, filepath, &text->width,
		&text->height);
	text->data = mlx_get_data_addr(text->ptr, &text->bpp, &text->size_line,
		&text->endian);
}

void	load_sprite(char *filepath, t_sprite *text, t_env *env)
{
	text->ptr = mlx_xpm_file_to_image(env->mlx, filepath, &text->width,
		&text->height);
	text->data = mlx_get_data_addr(text->ptr, &text->bpp, &text->size_line,
		&text->endian);
}

void	load_floor_or_ceil(char* arg1, char*arg2, t_env *env)
{
	int	color;

	if (ft_strcmp(arg1, "F") == 0)
	{
		if((color = is_rgb(arg2)) != -1)
		{
			env->has_text_floor = 0;
			env->color_floor = color;
		}
		else
		{
			try_filepath(arg2, env);
			env->has_text_floor = 1;
			load_texture(arg2, env->textF, env);
		}
	}
	else
	{
		if((color = is_rgb(arg2)) != -1)
		{
			env->has_text_ceiling = 0;
			env->color_ceiling = color;
		}
		else
		{
			try_filepath(arg2, env);
			env->has_text_ceiling = 1;
			load_texture(arg2, env->textC, env);
		}
	}
}