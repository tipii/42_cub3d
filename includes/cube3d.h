/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:37:21 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:37:16 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "env.h"
# include "keys.h"
# include "get_next_line.h"
# include "parse.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

void		init_env(t_env *env);
void		draw_column(t_env *env);
void		render(t_env *env);
void		calc_dist(t_env *env);
void		sprite_casting(t_env *env);
int			generate_color(int r, int g, int b);
double		deg_to_radian(double deg);
int			hook_keydown(int key, t_env *env);
int			hook_keyup(int key, t_env *env);
int			calc_player_pos(t_env *env);
int			get_pxl_clr_value(int x, int y, t_text *text);
int			get_pxl_sprite_value(int x, int y, t_sprite *text);
void		put_pxl_clr(int x, int y, unsigned int color, t_env *env);
void		error(char *message, t_env *env);
void		try_filepath(char *filepath, t_env *env);

#endif
