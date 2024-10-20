/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/20 02:05:44 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_point_array(t_grid	*grid)
{
	free(grid->pts_array);
	free(grid);
}

void	wipe(t_display *display)
{
	if (display)
	{
		if (display->img.mlx_img)
			mlx_destroy_image(display->link, display->img.mlx_img);
		free_point_array(display->grid);
		mlx_destroy_window(display->link, display->window);
		mlx_destroy_display(display->link);
		free(display->link);
	}
}

t_point	rotate_z(t_point point, t_display *display)
{
	int	tmp;

	tmp = point.x;
	point.x = tmp * cos(display->gamma) - point.y * sin(display->gamma);
	point.y = tmp * sin(display->gamma) + point.y * cos(display->gamma);
	fprintf(stderr, "point is {%d, %d, %d}\n", point.x, point.y, point.z);
	return (point);
}

t_point rotate_y(t_point point, t_display *display)
{
	int	tmp;

	tmp = point.x;
	point.x = tmp * cos(display->tetha) + point.z * sin(display->tetha);
	point.z = point.z * sin(display->tetha) - tmp * cos(display->tetha);
	fprintf(stderr, "point is {%d, %d, %d}\n", point.x, point.y, point.z);
	return (point);
}

t_point rotate_x(t_point point, t_display *display)
{
	int	tmp;

	tmp = point.y;
	point.x = tmp * cos(display->alpha) - point.z * sin(display->alpha);
	point.z = tmp * sin(display->alpha) + point.z * cos(display->alpha);
	return (point);
}

void	rotate(t_display *display)
{
	int	i;

	i = 0;
	while (i < display->grid->pts_count)
	{
		display->grid->pts_array[i] = rotate_x(display->grid->pts_array[i], display);
		i++;
	}
	render(display);
}

int	handle_intput(int keysym, t_display *display)
{
	if (keysym == XK_Escape)
	{
		wipe(display);
		exit(0);
	}
	if (keysym == XK_Up)
	{
		display->zoom += 10;
		render(display);
	}
	if (keysym == XK_Down)
	{
		display->zoom -= 10;
		render(display);
	}
	if (keysym == XK_r)
	{
		display->alpha += 10;
		rotate(display);
	}
	if (keysym == XK_R)
	{
		display->alpha -= 10;
		rotate(display);
	}
	if (keysym == XK_a)
	{
		display->offset_y += 10;
		display->offset_x -= 10;
		render(display);
	}
	if (keysym == XK_d)
	{
		display->offset_y -= 10;
		display->offset_x += 10;
		render(display);
	}
	if (keysym == XK_s)
	{
		display->offset_x += 10;
		display->offset_y += 10;
		render(display);
	}
	if (keysym == XK_w)
	{
		display->offset_x -= 10;
		display->offset_y -= 10;
		render(display);
	}
	return (0);
}

t_display	init_display(char *map_filepath)
{
	t_display	display;

	display.link = mlx_init();
	exit_if(!display.link, "mlx init\n", &display);
	display.window = mlx_new_window(display.link, WIN_WIDTH, WIN_HEIGHT, "FDF");
	exit_if((!display.window), "window allocation\n", &display);
	display.img.mlx_img = mlx_new_image(display.link, WIN_WIDTH, WIN_HEIGHT);
	exit_if(!display.img.mlx_img, "image allocation\n", &display);
	display.img.address = mlx_get_data_addr(display.img.mlx_img,
			&display.img.bit_per_pixel, &display.img.line_len,
			&display.img.endian);
	parse_file_into_grid(map_filepath, &display);
	render(&display);
	return (display);
}
