/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:37:21 by tpalhol           #+#    #+#             */
/*   Updated: 2019/12/06 15:29:11 by tpalhol          ###   ########.fr       */
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

//parse
int parse(char *filepath, t_env *env);

t_env		*init_env();
void		draw_column(t_env *env);
void		render(t_env *env);
int			generate_color(int r, int g, int b);
double		deg_to_radian(double deg);
int			hook_keydown(int key, t_env *env);

#endif