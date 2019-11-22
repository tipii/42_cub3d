/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:52:34 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/22 19:59:31 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_player *init_player()
{
	t_player *player;

	if(!(player = malloc(sizeof(t_player))))
		return (NULL);
	create_player(player, 1, 1);
	return (player);
}

