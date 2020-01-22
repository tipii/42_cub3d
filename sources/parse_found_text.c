/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_found_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:07:03 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:11:08 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		found_textn(t_env *env, t_checks *c)
{
	if (c->found_textn)
		error("NO texture is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 2, env);
	try_filepath(c->args[1], env);
	load_texture(c->args[1], env->text[3], env);
	c->found_textn = 1;
}

void		found_texts(t_env *env, t_checks *c)
{
	if (c->found_texts)
		error("SO texture is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 2, env);
	try_filepath(c->args[1], env);
	load_texture(c->args[1], env->text[1], env);
	c->found_texts = 1;
}

void		found_textw(t_env *env, t_checks *c)
{
	if (c->found_textw)
		error("WE texture is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 2, env);
	try_filepath(c->args[1], env);
	load_texture(c->args[1], env->text[2], env);
	c->found_textw = 1;
}

void		found_texte(t_env *env, t_checks *c)
{
	if (c->found_texte)
		error("EA texture is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 2, env);
	try_filepath(c->args[1], env);
	load_texture(c->args[1], env->text[0], env);
	c->found_texte = 1;
}

void		found_textsprites(t_env *env, t_checks *c)
{
	if (c->found_sprite)
		error("Sprite texture is defined multiple times", env);
	check_args_number(ft_tablen(c->args), 2, env);
	try_filepath(c->args[1], env);
	while (env->jsprite < env->countsprite)
	{
		load_sprite(c->args[1], env->sprites[env->jsprite], env);
		env->jsprite++;
	}
	c->found_sprite = 1;
}
