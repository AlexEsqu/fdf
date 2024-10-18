/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:50:50 by mkling            #+#    #+#             */
/*   Updated: 2024/10/18 23:24:58 by mkling           ###   ########.fr       */
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

void	put_point(t_display *display, t_pts *pts)
{
	char	*pixel;
	int		i;

	// if (pts->x < 0 || pts->x > WIN_WIDTH
	// 	|| pts->y < 0 || pts->y > WIN_WIDTH)
	// 	return ;
	i = display->img.bit_per_pixel - 8;
	pixel = display->img.address + (pts->y * display->img.line_len
			+ pts->x * (display->img.bit_per_pixel / 8));
	while (i >= 0)
	{
		if (display->img.endian != 0)
			*pixel++ = (pts->color >> i) & 0xFF;
		else
			*pixel++ = (pts->color >> (display->img.bit_per_pixel
						- 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	paint_background(t_image *img, int color)
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
}

void	print_grid(t_display *display)
{
	int	index;

	index = 0;
	while (index < display->grid->pts_count)
		put_point(display, &display->grid->pts_array[index++]);
	index = 1;
	while (index < display->grid->pts_count)
	{
		if (index % display->grid->col_count != 0)
			plot_line(&display->grid->pts_array[index - 1],
				&display->grid->pts_array[index], display);
		if (index > display->grid->row_count)
			plot_line(&display->grid->pts_array[index - display->grid->col_count],
				&display->grid->pts_array[index], display);
		index++;
	}
}

int	render(t_display *display)
{
	if (display->window == NULL)
		return (1);
	paint_background(&display->img, 0x000000);
	print_grid(display);
	plot_line(&display->grid->pts_array[0],
		&display->grid->pts_array[1], display);
	mlx_put_image_to_window(display->link, display->window,
		display->img.mlx_img, 0, 0);
	return (0);
}
