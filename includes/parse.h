/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:26:57 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 16:26:32 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int			ft_strlen(char *str);
int			ft_tablen(char **tab);
int			nbr_of_words(char const *s, char c);
char		*ft_cpy(char const *s, char c, char *tab, int i);
char		**free_all(char **tab, int i);
char		**no_str(char **tab);
char		**ft_split(char const *s, char c);
int			ft_atoi(char *s);
void		ft_freetab(char **tab);
int			ft_strcmp(const char *s1, const char *s2);
void		init_checks(t_checks *c);


#endif