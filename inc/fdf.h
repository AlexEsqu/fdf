/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:52:14 by mkling            #+#    #+#             */
/*   Updated: 2024/10/24 17:30:55 by mkling           ###   ########.fr       */
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

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define HEXADECIMAL "0123456789ABCDEF"
# define SMOLHEXADEC "0123456789abcdef"
# define ACCEPT_CHAR "abcdefABCDEF0123456789,x-+ "
# define BLACK 0x000000
# define WHITE 0xffffff
# define PI				3.14159265358979323846
# define PI_BY_FOUR		0.78539816339
# define PI_BY_SIX		0.52359877559
# define PI_BY_180		0.01745329251

typedef unsigned char	t_byte;

enum	e_error
{
	SUCCESS = 0,
	MALLOC_ERR = 1,
};

typedef	struct s_hsv
{
	int		alpha;
	float	hue;
	float	saturation;
	float	value;
}	t_hsv;

typedef	struct s_rgb
{
	int		alpha;
	float	red;
	float	green;
	float	blue;
}	t_rgb;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		dy;
	int		dx;
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
	int		zoom;
	int		unit;
	float	tetha;
	float	alpha;
	float	gamma;
	t_image	img;
	t_grid	*grid;
}	t_display;

/* DISPLAY */

t_display	init_display(char *map_filepath);
void		wipe(t_display *display);
int			handle_input(int keysym, t_display *display);
int			handle_mouse(int button, int x, int y, t_display *display);
int			success_exit(t_display *display);

/* PAINTING */

void	put_pixel(t_image *image, int x, int y, int color);
void	put_point(t_display *display, t_point point);
void	paint_background(t_image *image, int color);
int		render(t_display *display);
t_point	apply_zoom_and_offset(t_point *point, t_display *display);
t_point	isometrify(t_point point);

/* COLORING */

void	extract_color(t_point *point, char *hexacode);

/* PLOTTING */
void	plot_line(t_point origin, t_point end, t_display *display);

/* PARSING */
void	parse_file_into_grid(char *map_filepath, t_display *display);

/* ROTATING */
void	rotate(t_display *display, float angle, char axis);

/* ERRORS */
void	exit_if(bool condition, char *error_message, t_display *display);

#endif
