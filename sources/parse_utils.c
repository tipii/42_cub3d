/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:27:40 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/20 16:49:45 by tpalhol          ###   ########.fr       */
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

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int		is_charset(char c)
{
	int		i;
	char	*charset;

	i = 0;
	charset = "012NSEW ";
	while(charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}