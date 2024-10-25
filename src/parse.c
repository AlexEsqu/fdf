/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:19:45 by mkling            #+#    #+#             */
/*   Updated: 2024/10/25 11:05:10 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	open_file(char *map_filepath, t_display *display)
{
	int	fd;
	int	fd_len;

	fd_len = ft_strlen(map_filepath);
	exit_if((ft_strcmp(&map_filepath[fd_len - 4], ".fdf") != 0),
		"map file is not .fdf suffixed\n", display);
	fd = open(map_filepath, O_RDONLY);
	exit_if(fd < 0, "failed to open the map file\n", display);
	return (fd);
}

void	check_syntax(char *line, t_display *display)
{
	char	*acceptable;

	acceptable = ACCEPT_CHAR;
	while (*line++)
	{
		exit_if((ft_strchr(acceptable, *line) == 0 && *line != '\n'),
			"map file contains bad values\n", display);
	}
}

void	check_grid_size_syntax(char *map_filepath, t_grid *grid,
	t_display *display)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open_file(map_filepath, display);
	line_count = 0;
	line = get_next_line(fd);
	grid->width = countword(line, ' ');
	while (line != NULL)
	{
		line_count++;
		check_syntax(line, display);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	grid->pts_count = 0;
	grid->height = line_count;
}

t_point	turn_into_pts(char *map_point, t_display *display)
{
	t_point	point;
	char	**values;

	point.y = display->grid->pts_count / display->grid->width;
	point.x = display->grid->pts_count % display->grid->width;
	if (ft_strchr(map_point, ',') == 0)
	{
		point.z = ft_atoi(map_point);
		point.rgb = WHITE;
		return (point);
	}
	values = ft_split(map_point, ',');
	point.z = ft_atoi(values[0]);
	extract_color(&point, values[1]);
	ft_free_tab(values);
	return (point);
}

void	split_line_into_pts(char *line, t_display *display)
{
	char	**split_line;
	int		index;

	split_line = ft_split(line, ' ');
	exit_if((split_line == NULL), "malloc error", display);
	index = 0;
	while (split_line[index])
	{
		display->grid->pts_array[display->grid->pts_count]
			= turn_into_pts(split_line[index], display);
		display->grid->pts_count++;
		index++;
	}
	ft_free_tab(split_line);
}

void	parse_file_into_grid(char *map_filepath, t_display *display)
{
	int		fd;
	char	*line;

	display->offset_x = WIN_WIDTH;
	display->offset_y = WIN_HEIGHT / 2;
	display->unit = 1;
	display->zoom = 10;
	display->alpha = 0;
	display->tetha = 0;
	display->gamma = 0;
	display->grid = ft_calloc(1, sizeof(t_grid));
	check_grid_size_syntax(map_filepath, display->grid, display);
	fd = open_file(map_filepath, display);
	display->grid->pts_array = ft_calloc((display->grid->height
				* display->grid->width), sizeof(t_point));
	line = get_next_line(fd);
	while (line)
	{
		split_line_into_pts(line, display);
		free(line);
		line = get_next_line(fd);
	}
}
