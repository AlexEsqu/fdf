/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:50:50 by mkling            #+#    #+#             */
/*   Updated: 2024/10/18 18:24:31 by mkling           ###   ########.fr       */
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

void	put_point(t_display *display, t_pts pts)
{
	char	*pixel;
	int		i;

	i = display->img.bit_per_pixel - 8;
	pixel = display->img.address + (pts.y * display->img.line_len * display->zoom
			+ (pts.x * display->zoom) * (display->img.bit_per_pixel / 8));
	while (i >= 0)
	{
		if (display->img.endian != 0)
			*pixel++ = (pts.color >> i) & 0xFF;
		else
			*pixel++ = (pts.color >> (display->img.bit_per_pixel
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
	{
		// fprintf(stderr, "printing pts %d:\t (x:%d, y:%d, z:%d)\n", index,
		// 	display->grid->pts_array[index].x,
		// 	display->grid->pts_array[index].y,
		// 	display->grid->pts_array[index].z);
		put_point(display, display->grid->pts_array[index]);
		index++;
	}
}

int	render(t_display *display)
{

	if (display->window == NULL)
		return (1);
	display->offset_x = WIN_WIDTH / 2;
	display->offset_y = WIN_HEIGHT / 2;
	display->zoom = 20;
	paint_background(&display->img, 0x000000);
	
	print_grid(display);
	plot_line(&display->grid->pts_array[0],
		&display->grid->pts_array[10], display);
	mlx_put_image_to_window(display->link, display->window,
		display->img.mlx_img, 0, 0);
	return (0);
}
