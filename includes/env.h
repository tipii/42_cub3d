/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpalhol <tpalhol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 16:26:53 by tpalhol           #+#    #+#             */
/*   Updated: 2020/01/21 16:52:40 by tpalhol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef	struct	s_checks
{
	int			found_res;
	int			found_player;
	int			found_map;
	int			found_textn;
	int			found_texts;
	int			found_texte;
	int			found_textw;
	int			found_sprite;
	int			found_ceiling;
	int			found_floor;
	int			fd;
	char		**line;
	char		**args;
	int			i;
	int			j;
	int			k;
}				t_checks;

typedef struct	s_text
{
	void		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	char		*data;
}				t_text;

typedef struct	s_sprite
{
	void		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
	char		*data;
	int			spos_x;
	int			spos_y;
}				t_sprite;

typedef	struct	s_env
{
	double		posx;
	double		posy;
	double		t_speed;
	double		r_speed;
	double		dirx;
	double		diry;
	double		olddirx;
	double		olddiry;
	int			resx;
	int			resy;
	char		**map;
	int			mapwidth;
	int			mapheight;
	int			mapx;
	int			mapy;
	double		planex;
	double		planey;
	double		oldplanex;
	int			x;
	int			y;
	double		camerax;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		wallx;
	int			texx;
	int			texy;
	double		step;
	double		texpos;
	double		floorx_wall;
	double		floory_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	double		current_floorx;
	double		current_floory;
	int			floor_textx;
	int			floor_texty;
	int			ceil_textx;
	int			ceil_texty;
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
	int			bpp;
	int			size_line;
	int			endian;
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	float		lumvalue;
	int			lum;
	int			lineheight;
	int			drawstart;
	int			drawend;
	t_text		**text;
	t_text		*textf;
	t_text		*textc;
	int			has_text_floor;
	int			has_text_ceiling;
	int			color_floor;
	int			color_ceiling;
	t_checks	*c;
	int			malloc_check;
	int			malloc_map;
	int			malloc_sprites;
	int			malloc_textures;
	int			malloc_textures_floor;
	int			malloc_textures_ceiling;
	int			rotate_left;
	int			rotate_right;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
}				t_env;

void			init_map(int width, int height, t_env *env);
void			init_sprite(int i, t_env *env);
void			show_map(t_env *env);
void			get_lum_value(t_env *env);
void			sprite_casting(t_env *env);
void			set_player_value(char c, t_env *env);
void			load_texture(char *filepath, t_text *text, t_env *env);
void			load_sprite(char *filepath, t_sprite *text, t_env *env);
void			load_floor_or_ceil(char *arg1, char *arg2, t_env *env);
void			draw_floor(t_env *env);
void			move_forward(t_env *env);
void			move_backward(t_env *env);
void			move_left(t_env *env);
void			move_right(t_env *env);
int				is_rgb(char *arg);

#endif
