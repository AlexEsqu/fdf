/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:50:50 by mkling            #+#    #+#             */
/*   Updated: 2024/10/15 17:46:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bit_per_pixel - 8;
	pixel = img->address + (y * img->line_len + x
			* (img->bit_per_pixel / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bit_per_pixel - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	paint_background(t_image *img, int color)
{
	int	row;
	int	column;

	row = 0;
	while (row < WIN_HEIGHT)
	{
		column = 0;
		while (column < WIN_WIDTH)
			put_pixel(img, column++, row, color);
		++row;
	}
	return (0);
}

int	render(t_display *display)
{
	t_pts	origin;
	t_pts	end;

	if (display->window == NULL)
		return (1);
	paint_background(&display->img, 0x0000ff);
	origin.x = 1;
	origin.y = 1;
	end.x = 1;
	end.y = 500;
	plot_line(&origin, &end, display);
	mlx_put_image_to_window(display->link, display->window,
		display->img.mlx_img, 0, 0);
	return (0);
}
