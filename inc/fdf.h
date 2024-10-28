/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:52:14 by mkling            #+#    #+#             */
/*   Updated: 2024/10/27 17:45:30 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/inc/libft.h"

# define WIN_WIDTH		1200
# define WIN_HEIGHT		1200
# define HEXADECIMAL	"0123456789ABCDEF"
# define SMOLHEXADEC	"0123456789abcdef"
# define ACCEPT_CHAR	"abcdefABCDEF0123456789,x-+ "
# define PI				3.1415926535
# define PI_BY_FOUR		0.7853981633
# define PI_BY_SIX		0.5235987755
# define PI_BY_180		0.0174532925
# define ARCTAN			0.955316618

typedef unsigned char	t_byte;

enum	e_error
{
	SUCCESS = 0,
	MALLOC_ERR = 1,
};

enum	e_colors
{
	BLACK = 0x000000,
	WHITE = 0xffffff,
	MATRIX_START = 0x00ff60,
	MATRIX_END = 0x000800,
	SUNSET_START = 0xFF7E5F,
	SUNSET_END = 0xFEB47B,
	OCEAN_START = 0x00C9FF,
	OCEAN_END = 0x92FE9D,
	PURPLE_START = 0xA18CD1,
	PURPLE_END = 0xFBC2EB,
	FLAME_START = 0xFF9A9E,
	FLAME_END = 0xFAD0C4,
	COOL_START = 0x2193B0,
	COOL_END = 0x6DD5ED,
	EMERALD_START = 0x348F50,
	EMERALD_END = 0x56B4D3,
	SUNNY_START = 0xFF512F,
	SUNNY_END = 0xF09819,
	AUTUMN_START = 0xD38312,
	AUTUMN_END = 0xA83279,
};

enum	e_mouse
{
	RIGHT_CLICK = 1,
	LEFT_CLICK = 3,
	WHEEL_UP = 4,
	WHEEL_DOWN = 5,
};

typedef struct s_hsv
{
	int		alpha_;
	float	hue;
	float	sat;
	float	value;
}	t_hsv;

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		rgb;
	t_hsv	hsv;
}	t_point;

typedef struct s_line
{
	t_point	start;
	t_point	current;
	t_point	end;
	t_point	delta;
	t_point	sign;
	int		error;
	int		error2;
	float	length;
}	t_line;

typedef struct s_image
{
	void	*mlx_img;
	char	*address;
	int		bit_per_pixel;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_grid
{
	t_point	*pts_array;
	int		width;
	int		height;
	int		pts_count;
}	t_grid;

typedef struct s_display
{
	void	*link;
	void	*window;
	int		offset_x;
	int		offset_y;
	int		unit;
	float	elevation;
	float	zoom;
	int		color_mode;
	float	angle_y_axis;
	float	angle_x_axis;
	float	angle_z_axis;
	t_image	img;
	t_grid	*local;
	t_grid	*world;
}	t_display;

/* DISPLAY */

t_display	init_display(char *map_filepath);
void		wipe(t_display *display);
int			handle_input(int keysym, t_display *display);
int			handle_mouse(int button, int x, int y, t_display *display);
int			success_exit(t_display *display);
void		free_grid(t_grid *grid);

/* PAINTING */

void		put_pixel(t_image *image, int x, int y, int color);
void		put_point(t_display *display, t_point point);
void		paint_background(t_image *image, int color);
void		reinitialize_world_grid(t_display *display);
int			render(t_display *display);

/* COLORING */

void		extract_color(t_point *point, char *hexacode);
int			get_red(int color);
int			get_green(int color);
int			get_blue(int color);
int			encode_rgb(t_byte red, t_byte green, t_byte blue);
int			interpolate_rgb_gradient(int start_rgb, int end_rgb,
				float progress);
int			interpolate_hsv_gradient(int start_rgb, int end_rgb,
				float progress);
void		assign_color(t_display *display);

/* PLOTTING */

void		plot_line(t_point origin, t_point end, t_display *display);
float		calculate_line_length(t_point start, t_point end);
void		subtract_grid_center(t_point *point, t_display *display);
void		add_grid_center(t_point *point, t_display *display);
void		add_elevation(t_display *display);
t_point		apply_zoom_and_offset(t_point *point, t_display *display);

/* PARSING */

void		parse_file_into_grid(char *map_filepath, t_display *display);

/* ROTATING */

void		rotate(t_display *display);
void		isometrify(t_display *display);
void		top_view(t_display *display);
void		front_view(t_display *display);
void		right_view(t_display *display);

/* ERRORS */

void		exit_if(bool condition, char *error_message, t_display *display);

#endif
