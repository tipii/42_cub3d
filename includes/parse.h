/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:26:57 by tpalhol           #+#    #+#             */
/*   Updated: 2019/12/06 15:31:58 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int			ft_strlen(char *str);
int			nbr_of_words(char const *s, char c);
char		*ft_cpy(char const *s, char c, char *tab, int i);
char		**free_all(char **tab, int i);
char		**no_str(char **tab);
char		**ft_split(char const *s, char c);


#endif