/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:35:22 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 16:34:15 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int				is_c(char c, char *charset)
{
	int			count;

	count = 0;
	while (charset[count])
	{
		if (charset[count] == c)
			return (1);
		count++;
	}
	return (0);
}

int				count_words(char *str, char *charset)
{
	int			count;
	int			i;

	count = 1;
	i = 0;
	while (str[i] && is_c(str[i], charset))
		i++;
	while (str[i])
	{
		if (is_c(str[i], charset) && !(is_c(str[i - 1], charset)))
		{
			while (is_c(str[i], charset))
				i++;
			count++;
		}
		else
			i++;
	}
	if (is_c(str[i - 1], charset))
		count--;
	return (count);
}

char			*ft_cpy(char *str, char *tab, int i, char *charset)
{
	int j;
	int k;
	int l;

	k = i;
	j = 0;
	l = 0;
	while (str[i] && !(is_c(str[i], charset)))
	{
		i++;
	}
	if (!(tab = malloc(sizeof(char) * (i - k + 1))))
		return (NULL);
	while (l < i - k)
	{
		tab[l] = str[k + l];
		l++;
	}
	tab[l] = 0;
	return (tab);
}

char			**ft_split(char *str, char *charset)
{
	char		**res;
	int			it[3];

	it[0] = 0;
	it[1] = 0;
	it[2] = 0;
	str[0] != 0 ? it[1] = count_words(str, charset) : it[1];
	res = malloc(sizeof(char *) * (it[1] + 1));
	if (str[0] != 0)
	{
		while (str[it[0]] && is_c(str[it[0]], charset))
			it[0]++;
		while (str[it[0]])
		{
			if (!(is_c(str[it[0]], charset)) && (is_c(str[it[0] - 1], charset)
						|| it[0] < 1) && it[2] < it[1])
			{
				res[it[2]] = ft_cpy(str, res[it[2]], it[0], charset);
				it[2]++;
			}
			it[0]++;
		}
	}
	res[it[1]] = 0;
	return (res);
}
