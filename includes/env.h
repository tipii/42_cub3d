/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:26:53 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/26 19:56:04 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define FOV 60
# define H_WALL 64
# define H_PLAYER 64

typedef	struct	s_env
{
	int			res_x;
	int			res_y;
	int			h_wall;
	int			h_player;
	int			fov;
	float		dist_player_screen;
	int			**map;

}				t_env;

int	**init_map(int width, int height);

#endif