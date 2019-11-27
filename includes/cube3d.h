/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:37:21 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 09:33:45 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "env.h"
# include "keys.h"
# include "player.h"

# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

void		init_all(t_player *player, t_env *env);
t_env		*init_env(t_player *player);
t_player	*init_player();
void		draw_vert_line(t_env *env);
void		raytrace(t_env *env, t_player *player);
int			generate_color(int r, int g, int b);
double		deg_to_radian(double deg);

#endif