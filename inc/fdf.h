/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:52:14 by mkling            #+#    #+#             */
/*   Updated: 2024/10/23 18:21:05 by mkling           ###   ########.fr       */
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
# define HEXADECIMAL "ABCDEF0123456789"
# define SMOLHEXADEC "abcdef0123456789"
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

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		dy;
	int		dx;
	int		color;
}	t_point;

typedef struct s_line
{
	t_point	origin;
	t_point	end;
	t_point	delta;
	t_point	sign;
	int		error;
	int		error2;
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
	double	tetha;
	double	alpha;
	double	gamma;
	t_image	img;
	t_grid	*grid;
}	t_display;

/* DISPLAY */
t_display	init_display(char *map_filepath);
void		wipe(t_display *display);
int			handle_input(int keysym, t_display *display);
int			handle_mouse(int button, int x, int y, t_display *display);

/* PAINTING */
void	put_pixel(t_image *image, int x, int y, int color);
void	put_point(t_display *display, t_point point);
int		encode_rgb(t_byte red, t_byte green, t_byte blue);
void	paint_background(t_image *image, int color);
int		render(t_display *display);
t_point	apply_zoom_and_offset(t_point *point, t_display *display);
t_point	isometrify(t_point point);

/* PLOTTING */
void	plot_line(t_point origin, t_point end, t_display *display);

/* PARSING */
void	parse_file_into_grid(char *map_filepath, t_display *display);

/* ROTATING */
void	rotate_z_axis(t_display *display);
void	rotate_y_axis(t_display *display);
void	rotate_x_axis(t_display *display);

/* ERRORS */
void	exit_if(bool condition, char *error_message, t_display *display);

#endif
