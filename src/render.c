/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:50:50 by mkling            #+#    #+#             */
/*   Updated: 2024/10/26 15:49:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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

void	put_point(t_display *display, t_point point)
{
	char	*pixel;
	int		i;

	if (point.x < 0 || point.y < 0
		|| point.x > WIN_WIDTH || point.y > WIN_HEIGHT)
		return ;
	i = display->img.bit_per_pixel - 8;
	pixel = display->img.address + ((int)point.y * display->img.line_len
			+ (int)point.x * (display->img.bit_per_pixel / 8));
	while (i >= 0)
	{
		if (display->img.endian != 0)
			*pixel++ = (point.rgb >> i) & 0xFF;
		else
			*pixel++ = (point.rgb >> (display->img.bit_per_pixel
						- 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	print_grid(t_grid *grid, t_display *display)
{
	int		index;

	index = 0;
	while (index < grid->pts_count)
	{
		if (index % grid->width != 0)
		{
			plot_line(grid->pts_array[index - 1],
				grid->pts_array[index], display);
		}
		if (index >= grid->width)
		{
			plot_line(grid->pts_array[index - grid->width],
				grid->pts_array[index], display);
		}
		index++;
	}
}

int	render(t_display *display)
{
	if (display->window == NULL)
		return (1);
	paint_background(&display->img, BLACK);
	if (display->color_mode)
		assign_color(display);
	rotate(display);
	print_grid(display->world, display);
	mlx_put_image_to_window(display->link, display->window,
		display->img.mlx_img, 0, 0);
	// printf("new render\n");
	reinitialize_world_grid(display);
	return (0);
}

/*
printf("first pixel = %f, %f, %f\n", display->grid->pts_array[1].x,
		display->grid->pts_array[1].y, display->grid->pts_array[1].z);
*/
