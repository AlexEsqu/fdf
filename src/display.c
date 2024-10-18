/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/18 17:27:38 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_point_array(t_grid	*grid)
{
	free(grid->pts_array);
	free(grid);
}

void	wipe_window(t_display *display)
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

void	error_exit(char *error_message, t_display *display)
{
	if (error_message)
		ft_putstr_fd(error_message, 2);
	if (display)
		wipe_window(display);
	exit(1);
}

void	success_exit(t_display *display)
{
	wipe_window(display);
	exit(0);
}

int	handle_intput(int keysym, t_display *display)
{
	if (keysym == XK_Escape)
		success_exit(display);
	return (0);
}

t_display	init_display(char *map_filepath)
{
	t_display	display;

	display.link = mlx_init();
	if (!display.link)
		error_exit("mlx init\n", &display);
	display.window = mlx_new_window(display.link,
			WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!display.window)
		error_exit("window allocation\n", &display);
	display.img.mlx_img = mlx_new_image(display.link, WIN_WIDTH, WIN_HEIGHT);
	if (!display.img.mlx_img)
		error_exit("image allocation\n", &display);
	display.img.address = mlx_get_data_addr(display.img.mlx_img,
			&display.img.bit_per_pixel, &display.img.line_len,
			&display.img.endian);
	parse_file_into_grid(map_filepath, &display);
	mlx_loop_hook(display.link, &render, &display);
	mlx_hook(display.window, KeyPress, KeyPressMask, &handle_intput, &display);
	mlx_loop(display.link);
	return (display);
}
