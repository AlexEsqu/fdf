/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:52:14 by mkling            #+#    #+#             */
/*   Updated: 2024/10/09 17:31:19 by mkling           ###   ########.fr       */
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
# include <X11/keysym.h>
# include <X11/X.h>
# include "../lib/minilibx/mlx.h"
# include "../lib/libft/inc/libft.h"

# define WIN_WIDTH 500
# define WIN_HEIGHT 500

typedef unsigned char	t_byte;

enum	e_error
{
	SUCCESS = 0,
	MALLOC_ERR = 1,
};

enum	e_dimension
{
	X = 0,
	Y = 1,
};

typedef struct s_image
{
	void	*mlx_img;
	char	*address;
	int		bit_per_pixel;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_display
{
	void	*link;
	void	*window;
	int		size_x;
	int		size_y;
	char	*title;
	t_image	img;
}	t_display;

typedef struct s_point
{
	int		x;
	int		y;
}	t_pts;

typedef struct s_line
{
	t_pts	origin;
	t_pts	end;
	t_pts	direction;
	t_pts	sign;
	int		error;
	int		error2;
}	t_line;

typedef struct s_drawing
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_drawing;

/* DISPLAY */
t_display	init_display(void);
void		error_exit(char *error_message, t_display *display);
void		success_exit(t_display *display);

/* PAINTING */
void	img_pixel_put(t_image *image, int x, int y, int color);
int		encode_rgb(t_byte red, t_byte green, t_byte blue);
int		paint_background(t_image *image, int color);
int		paint_rectangle(t_image *image, t_drawing rectangle);
int		render(t_display *display);

/* PLOTTING */
void	plot_line(t_pts *origin, t_pts *end, t_display *display);



#endif
