/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/28 17:00:34 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_grid(t_grid *grid)
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
		free_grid(display->local);
		free_grid(display->world);
		mlx_destroy_window(display->link, display->window);
		mlx_destroy_display(display->link);
		free(display->link);
	}
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

void	initialize_window_and_offsets(t_display *display)
{
	display->offset_x = WIN_WIDTH / 2;
	display->offset_y = WIN_HEIGHT / 2;
	display->unit = 1;
	display->zoom = 10.0;
	display->angle_x_axis = 0;
	display->angle_y_axis = 0;
	display->angle_z_axis = 0;
	display->elevation = 1.0;
	display->color_mode = 1;
}
