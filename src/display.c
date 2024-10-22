/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/23 00:53:08 by mkling           ###   ########.fr       */
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
