/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:41:18 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/26 19:10:21 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# define START_POSX 2
# define START_POSY 2
typedef	struct	s_player
{
	float			pos_x;
	float			pos_y;
	float			v_angle;
	int				speed;
}				t_player;

void			create_player(t_player *player, float pos_x, float pos_y);
t_player		*init_player();

#endif