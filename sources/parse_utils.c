/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:27:40 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/09 12:43:43 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int ft_strlen(char *str)
{
	int i;
 
	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;

	return (i);
}

int ft_atoi(char *s)
{
	int atoi;
	int i;

	atoi = 0;
	i = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		atoi = atoi * 10 + (s[i] - 48);
		i++;
	}
	return (atoi);
}

void ft_freetab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}