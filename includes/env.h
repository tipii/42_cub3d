/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:26:53 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/19 19:06:01 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define FOV 60
# define H_WALL 64
# define H_PLAYER 64

typedef	struct s_checks
{
	int				found_res;
	int				found_player;
	int				found_map;
	int				found_textN;
	int				found_textS;
	int				found_textE;
	int				found_textW;
	int				found_sprite;
	int				found_ceiling;
	int				found_floor;
	int				fd;
	char			**line;
	char			**args;
	int				i;
	int				j;
	int				k;
}				t_checks;

typedef struct s_text
{
	void		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	char		*data;
}				t_text;

typedef struct s_sprite
{
	void		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	char		*data;
	int			posx;
	int			posy;
}				t_sprite;

typedef	struct	s_env
{
	///PLAYER INFOS
	double			posX;
	double			posY;
	double			t_speed;
	double			r_speed;
	/* direction of player */
	double			dirX;
	double			dirY;
	/* stock old dirX and dirY */
	double			oldDirX;
	double			oldDirY;
	/* resolution */
	int		resX;
	int		resY;
	/* height of wall / player */
	double		wallH;
	double		playerH;
	/* field of view */
	double		fov;
	/* map */
	char			**map;
	int				mapWidth;
	int				mapHeight;
	/* current pos on map */
	int			mapX;
	int			mapY;
	/* camera plane */
	double		planeX;
	double		planeY;
	double		oldPlaneX;
	double		oldPlaneY;
	/* definig wich ray (left -1 to right 1) and dir */
	int			x;
	int			y;
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
	/* textures variables */
	double		wallX;
	int			texX;
	double		step;
	double		texPos;
	int			texY;
	/* wall and floor variables */
	double		rayDirX0;
	double		rayDirY0;
	double		rayDirX1;
	double		rayDirY1;
	int			p;
	double		posZ;
	double		rowDistance;
	double		floorStepX;
	double		floorStepY;
	double		floorX;
	double		floorY;
	int			cellX;
	int			cellY;
	int			tx;
	int			ty;
	/* sprites */
	int			countsprite;
	int			isprite;
	int			jsprite;
	t_sprite	**sprites;
	double		*zbuffer;
	int			*s_order;
	double		*sprite_distance;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			spriteheight;
	int			drawstarty;
	int			drawendy;
	int			drawstartx;
	int			drawendx;
	int			spritewidth;
	int			stripe;
	int			d;
	int			color;
	/* mlx prop */
	int			bpp;
	int			size_line;
	int			endian;
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	/*DRAW*/
	float		lumvalue;
	int			lum;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	t_text		**text;
	t_text		*textsprite;
	t_text		*textF;
	t_text		*textC;
}				t_env;

void		init_map(int width, int height, t_env *env);
void		init_sprite(int i, t_env *env);
void		show_map(t_env *env);
void		error(char* message);
void		get_lum_value(t_env *env);
void		sprite_casting(t_env *env);

#endif