/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:26:57 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/22 17:51:08 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int			parse(char *filepath, t_env *env);
int			ft_strlen(char *str);
int			ft_tablen(char **tab);
int			nbr_of_words(char const *s, char c);
char		*ft_cpy(char *str, char *tab, int i, char *charset);
char		**free_all(char **tab, int i);
char		**no_str(char **tab);
char		**ft_split(char *s, char *c);
int			ft_atoi(char *s);
void		ft_freetab(char **tab);
int			ft_strcmp(const char *s1, const char *s2);
void		init_checks(t_checks *c);
int			is_charset(char c, char *charset);
void		check_map_is_close(t_env *env);
void		parse_map(t_env *env, t_checks *c);
void		add_line_to_map(t_env *env, t_checks *c);
void		check_args_number(int nbr, int expected, t_env *env);
void		found_textn(t_env *env, t_checks *c);
void		found_texts(t_env *env, t_checks *c);
void		found_texte(t_env *env, t_checks *c);
void		found_textw(t_env *env, t_checks *c);
void		found_textsprites(t_env *env, t_checks *c);
void		has_found_all(t_env *env);
void		found_res(t_env *env, t_checks *c);
void		found_sprite(t_env *env, t_checks *c);
void		found_player(t_env *env, t_checks *c);
void		found_floor(t_env *env, t_checks *c);
void		found_ceiling(t_env *env, t_checks *c);

#endif
