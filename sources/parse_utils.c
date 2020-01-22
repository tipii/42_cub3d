/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:27:40 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 16:25:19 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_atoi(char *str)
{
	long	atoi;
	int		neg;
	int		i;

	atoi = 0;
	neg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' ||
				str[i] == '\v' || str[i] == '\n' ||
				str[i] == '\r' || str[i] == '\f'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = (atoi * 10) + (str[i] - 48);
		i++;
	}
	if (atoi > 2147483647)
		atoi = 2147483647;
	atoi = atoi * neg;
	return (atoi);
}

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if(!s1 || (s1[i] == 0 || s2[i] == 0))
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
