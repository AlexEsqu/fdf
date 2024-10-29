/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:58:38 by mkling            #+#    #+#             */
/*   Updated: 2024/10/29 14:42:05 by mkling           ###   ########.fr       */
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

void	soft_exit_if(bool condition, char *error_mess)
{
	if (condition == false)
		return ;
	if (error_mess)
		ft_putstr_fd(error_mess, 2);
	exit(1);
}

void	check_line_syntax(char *line, t_display *display)
{
	int	i;

	soft_exit_if((display->grid_width != (int)countword(line, ' ')),
		"Missing inputs in a line\n");
	i = 0;
	while (line[i] != '\0')
	{
		if(ft_strchr(ACCEPT_CHAR, line[i]) == 0 && line[i] != '\n')
		{
			free(line);
			soft_exit_if(1, "Map file contains bad values\n");
		}
		i++;
	}
}

void	check_filename_syntax(char *map_filepath)
{
	int	fd_len;
	int	fd;

	fd_len = ft_strlen(map_filepath);
	soft_exit_if((ft_strcmp(&map_filepath[fd_len - 4], ".fdf") != 0),
		"map file is not .fdf suffixed\n");
	fd = open(map_filepath, O_RDONLY);
	soft_exit_if(fd < 0, "failed to open the map file\n");
	close(fd);
}

void	check_file_syntax(char *map_filepath, t_display *display)
{
	int		fd;
	int		line_count;
	char	*line;

	check_filename_syntax(map_filepath);
	fd = open_file(map_filepath, display);
	line_count = 0;
	line = get_next_line(fd);
	display->grid_width = countword(line, ' ');
	exit_if(display->grid_width == 0, "Grid width is 0\n", display);
	display->grid_width = display->grid_width;
	while (line != NULL)
	{
		line_count++;
		check_line_syntax(line, display);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	display->grid_point_count = 0;
	display->grid_height = line_count;
	soft_exit_if(display->grid_height == 0, "Grid height is 0\n");
	display->grid_height = display->grid_height;
}
