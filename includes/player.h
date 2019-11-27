/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:41:18 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 09:46:12 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# define START_POSX 1
# define START_POSY 1
typedef	struct	s_player
{
	/* position of player */
	double			posX;
	double			posY;
	/* direction of player */
	double			dirX;
	double			dirY;
	/* translation and rotation speed */
	double			t_speed;
	double			r_speed;
}				t_player;

void			create_player(t_player *player, double pos_x, double pos_y);
t_player		*init_player();

#endif