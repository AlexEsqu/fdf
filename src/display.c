/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:53:21 by mkling            #+#    #+#             */
/*   Updated: 2024/10/09 14:06:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	wipe_window(t_display *display)
{
	mlx_destroy_window(display->link, display->window);
	mlx_destroy_display(display->link);
	free(display->link);
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
	if (display->img.mlx_img)
		mlx_destroy_image(display->link, display->img.mlx_img);
	if (display)
		wipe_window(display);
	exit(0);
}

int	handle_intput(int keysym, t_display *display)
{
	
	if (keysym == XK_Escape)
		success_exit(display);
	if (keysym == XK_R)
	{
		mlx_destroy_image(display->link, display->img.mlx_img);
		paint_background(&display->img, 0xff0000);
		mlx_put_image_to_window(display->link, display->window,
			display->img.mlx_img, 0, 0);
	}
	return (0);
}

t_display	init_display(void)
{
	t_display	display;

	display.link = mlx_init();
	if (!display.link)
		error_exit("mlx init", &display);
	display.window = mlx_new_window(display.link,
			WIN_WIDTH, WIN_HEIGHT, "FDF");
	if (!display.window)
		error_exit("display init", &display);
	display.img.mlx_img = mlx_new_image(display.link, WIN_WIDTH, WIN_HEIGHT);
	display.img.address = mlx_get_data_addr(display.img.mlx_img,
			&display.img.bit_per_pixel, &display.img.line_len,
			&display.img.endian);
	mlx_loop_hook(display.link, &render, &display);
	mlx_hook(display.window, KeyPress, KeyPressMask, &handle_intput, &display);
	mlx_loop(display.link);
	return (display);
}
