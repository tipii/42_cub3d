/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:35:22 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 15:27:23 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			nbr_of_words(char const *s, char c)
{
	int		i;
	int		count;
	int		lens;

	lens = ft_strlen((char*)s);
	count = 1;
	i = 0;
	while (s && i < lens)
	{
		if (s[i] == c && s[i + 1] != 0 && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

char		*ft_cpy(char const *s, char c, char *tab, int i)
{
	int		j;
	int		k;

	j = i;
	k = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(tab = malloc(sizeof(char) * (i - j + 1))))
		return (NULL);
	while (k < i - j)
	{
		tab[k] = s[j + k];
		k++;
	}
	tab[k] = 0;
	return (tab);
}

char		**free_all(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char		**no_str(char **tab)
{
	tab[0] = NULL;
	return (tab);
}

char		**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		it_words;

	i = 0;
	it_words = 0;
	if (!(tab = malloc(sizeof(char*) * (nbr_of_words(s, c) + 1))))
		return (NULL);
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c) &&
		it_words < nbr_of_words(s, c))
		{
			tab[it_words] = ft_cpy(s, c, tab[it_words], i);
			if (tab[it_words] == NULL)
				return (free_all(tab, i));
			it_words++;
		}
		i++;
	}
	tab[it_words] = NULL;
	return (tab);
}
