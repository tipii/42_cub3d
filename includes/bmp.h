/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:23:13 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/27 15:49:55 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

typedef	struct		s_bmp
{
	int				fd;
	int				file_size;
	int				bpp;
	int				header_size;
	int				info_header_size;
	unsigned char	padding[3];
	int				padding_size;
	unsigned char	file_header[14];
	unsigned char	info_header[40];
}					t_bmp;

#endif
