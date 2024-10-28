/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/27 17:30:18 by alex             ###   ########.fr       */
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

int	success_exit(t_display *display)
{
	wipe(display);
	exit(0);
	return (0);
}

void	exit_if(bool condition, char *error_message, t_display *display)
{
	if (condition == false)
		return ;
	if (error_message)
		ft_putstr_fd(error_message, 2);
	if (display)
		wipe(display);
	exit(1);
}
