/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:50:50 by mkling            #+#    #+#             */
/*   Updated: 2024/10/09 17:43:03 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void	img_pixel_put(t_image *image, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = image->bit_per_pixel - 8;
	pixel = image->address + (y * image->line_len + x
			* (image->bit_per_pixel / 8));
	while (i >= 0)
	{
		if (image->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (image->bit_per_pixel - 8
						- i)) & 0xFF;
		i -= 8;
	}
}

int	paint_background(t_image *image, int color)
{
	int	line;
	int	column;

	line = 0;
	while (line < WIN_HEIGHT)
	{
		column = 0;
		while (column < WIN_WIDTH)
			img_pixel_put(image, column++, line, color);
		++line;
	}
	return (0);
}

int	paint_rectangle(t_image *image, t_drawing rectangle)
{
	int	columns;
	int	lines;

	columns = rectangle.y;
	while (columns < rectangle.x + rectangle.width)
	{
		lines = rectangle.x;
		while (lines < rectangle.x + rectangle.width)
			img_pixel_put(image, lines++, columns, rectangle.color);
		++columns;
	}
	return (0);
}

int	render(t_display *display)
{
	t_pts	origin;
	t_pts	end;

	if (display->window == NULL)
		return (1);
	origin.x = 200;
	origin.y = 200;
	end.x = 250;
	end.y = 250;
	paint_background(&display->img, 0x000022);
	plot_line(&origin, &end, display);
	mlx_put_image_to_window(display->link, display->window,
		display->img.mlx_img, 0, 0);
	return (0);
}

/*
paint_rectangle(&display->img, (t_drawing){WIN_WIDTH - 100, WIN_HEIGHT - 100, 100, 100, 0xFF0000});
paint_rectangle(&display->img, (t_drawing){100, 100, 100, 100, 0xFF0000});
*/
