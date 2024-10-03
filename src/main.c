/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:48:35 by mkling            #+#    #+#             */
/*   Updated: 2024/10/03 18:46:08 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clean_up(t_display *display)
{
	mlx_destroy_window(display->link, display->window);
	mlx_destroy_display(display->link);
	if (display->title)
		free(display->title);
	if (display->link)
		free(display->link);
	free(display);
}

void	error_exit(char *error_message, t_display *display)
{
	if (error_message)
		ft_putstr_fd(error_message, 2);
	if (display)
		clean_up(display);
	exit(MALLOC_ERR);
}

void	clean_up_exit(t_display *display)
{
	clean_up(display);
	exit(0);
}

int	handle_intput(int keysym, t_display *display)
{
	if (keysym == XK_Escape)
		clean_up_exit(display);
	return (0);
}

void	init_display(t_display *display)
{
	display->link = mlx_init();
	if (!display || !display->link)
		error_exit("mlx init", display);
	(display)->size_x = 500;
	(display)->size_y = 500;
	(display)->title = ft_strdup("FDF");
	(display)->window = mlx_new_window((display)->link,
			(display)->size_x, (display)->size_y, (display)->title);
	if (!(display)->window || !(display)->title)
		error_exit("display init", display);
	mlx_key_hook((display)->window, handle_intput, display);
	mlx_loop((display)->link);
}



int	main(int argc, char **argv)
{
	t_display	display;

	if (argc > 6 || argv[1] != NULL)
		return (1);
	init_display(&display);
	return (0);
}
