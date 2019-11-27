/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:26:53 by tpalhol           #+#    #+#             */
/*   Updated: 2019/11/27 10:08:41 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define FOV 60
# define H_WALL 64
# define H_PLAYER 64

typedef	struct	s_env
{
	/* resolution */
	int		resX;
	int		resY;
	/* height of wall / player */
	double		wallH;
	double		playerH;
	/* field of view */
	double		fov;
	/* map */
	int			**map;
	/* current pos on map */
	int			mapX;
	int			mapY;
	/* camera plane */
	double		planeX;
	double		planeY;
	/* definig wich ray (left -1 to right 1) and dir */
	int			x;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	/* ray dist to next case on map */
	double		sideDistX;
	double		sideDistY;
	/* length of ray from one x or y-side to next x or y-side */
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	/* step in x and y (-1 or +1) according to cam vector*/
	int			stepX;
	int			stepY;
	/* when a wall is hit */
	int			hit;
	/* side of wall */
	int			side;
	/* mlx prop */
	int			bpp;
	int			size_line;
	int			endian;
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	/*DRAW*/
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}				t_env;

int	**init_map(int width, int height);

#endif