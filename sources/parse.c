/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:59:27 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/22 18:47:09 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		create_player(t_player *player, float pos_x, float pos_y)
{
	player->pos_x = pos_x;
	player->pos_y = pos_y;
}
