/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:58:38 by mkling            #+#    #+#             */
/*   Updated: 2024/10/28 17:02:15 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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

void	check_syntax(char *line, t_display *display)
{
	exit_if((display->local->width != (int)countword(line, ' ')),
		"Missing inputs in a line\n", display);
	while (*line++)
	{
		exit_if((ft_strchr(ACCEPT_CHAR, *line) == 0 && *line != '\n'),
			"Map file contains bad values\n", display);
	}
}

void	check_grid_size_syntax(char *map_filepath, t_display *display)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open_file(map_filepath, display);
	line_count = 0;
	line = get_next_line(fd);
	display->local->width = countword(line, ' ');
	exit_if(display->local->width == 0, "Grid width is 0\n", display);
	display->world->width = display->local->width;
	while (line != NULL)
	{
		line_count++;
		check_syntax(line, display);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	display->local->pts_count = 0;
	display->local->height = line_count;
	exit_if(display->local->height == 0, "Grid height is 0\n", display);
	display->world->height = display->local->height;
}
