/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:48:35 by mkling            #+#    #+#             */
/*   Updated: 2024/10/03 18:02:13 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	error_exit(char *error_message, t_display *display)
{
	if (error_message != NULL)
		ft_putstr_fd(error_message, 2);
	if (display)
	{
		mlx_destroy_display(display->link);
		if (display->link)
			free(display->link);
		if (display->title)
			free(display->title);
		free(display);
	}
	exit(MALLOC_ERR);
}

void	init_display(t_display **display)
{
	(*display) = malloc(sizeof(t_display));
	(*display)->link = mlx_init();
	if (!(*display) || !(*display)->link)
		error_exit("mlx init", *display);
	(*display)->size_x = 100;
	(*display)->size_y = 100;
	(*display)->title = ft_strdup("FDF");
	(*display)->window = mlx_new_window((*display)->link,
			(*display)->size_x, (*display)->size_y, (*display)->title);
	if (!(*display)->window || !(*display)->title)
		error_exit("display init", *display);
	mlx_loop((*display)->link);
}

int	main(int argc, char **argv)
{
	t_display	*display;

	if (argc > 6 || argv[1] != NULL)
		return (1);
	init_display(&display);
	return (0);
}
