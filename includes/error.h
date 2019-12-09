/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 13:29:11 by tpalhol           #+#    #+#             */
/*   Updated: 2019/12/09 13:59:23 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define ERROR_MAP "MAP INTEGRITY"
# define ERROR_MAP_L_LENGTH "A LINE AS NOT A GOOD LENGTH"

typedef	struct	s_error
{
	int			std_line_length;
}				t_error;
#endif