/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:41:18 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/22 20:09:51 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

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