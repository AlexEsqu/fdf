/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:48:35 by mkling            #+#    #+#             */
/*   Updated: 2024/10/22 17:16:25 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;

	if (argc != 2)
		return (1);
	display = init_display(argv[1]);
	mlx_loop_hook(display.link, NULL, &display);
	mlx_hook(display.window, KeyPress, KeyPressMask, &handle_input, &display);
	mlx_loop(display.link);
	wipe(&display);
	return (0);
}
