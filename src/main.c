/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:48:35 by mkling            #+#    #+#             */
/*   Updated: 2024/10/29 14:27:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;

	if (argc != 2)
		return (1);
	check_file_syntax(argv[1], &display);
	parse_file_into_grid(argv[1], &display);
	init_window(&display);
	mlx_loop_hook(display.link, NULL, &display);
	isometrify(&display);
	render(&display);
	mlx_hook(display.window, KeyPress, KeyPressMask, &handle_input, &display);
	mlx_hook(display.window, DestroyNotify, LeaveWindowMask,
		&success_exit, &display);
	mlx_mouse_hook(display.window, &handle_mouse, &display);
	mlx_loop(display.link);
	wipe(&display);
	return (0);
}

int	success_exit(t_display *display)
{
	wipe(display);
	exit(0);
	return (0);
}
