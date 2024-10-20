/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:19:45 by mkling            #+#    #+#             */
/*   Updated: 2024/10/20 01:35:20 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	open_file(char *map_filepath)
{
	int	fd;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("failed to open the grid file\n", 2);
		exit(1);
	}
	return (fd);
}

void	check_syntax(char *line)
{
	char	*acceptable;

	acceptable = ACCEPT_CHAR;
	while (*line++)
	{
		if (ft_strchr(acceptable, *line) == 0 && *line != '\n')
		{
			ft_putstr_fd("grid file contains bad values\n", 2);
			exit(1);
		}
	}
}

void	check_grid_size_syntax(char *map_filepath, t_grid *grid)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open_file(map_filepath);
	line_count = 0;
	line = get_next_line(fd);
	grid->width = countword(line, ' ');
	while (line != NULL)
	{
		line_count++;
		check_syntax(line);
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
		point.color = WHITE;
		return (point);
	}
	values = ft_split(map_point, ',');
	point.z = ft_atoi(values[0]);
	point.color = ft_atoi(values[1]);
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
	int		index;
	char	*line;

	display->offset_x = WIN_WIDTH;
	display->offset_y = WIN_HEIGHT / 3;
	display->zoom = 15;
	display->alpha = 0;
	display->gamma = 0;
	display->tetha = 0;
	display->grid = ft_calloc(1, sizeof(t_grid));
	check_grid_size_syntax(map_filepath, display->grid);
	fd = open_file(map_filepath);
	display->grid->pts_array = ft_calloc((display->grid->height
				* display->grid->width), sizeof(t_point));
	index = 0;
	line = get_next_line(fd);
	while (line)
	{
		split_line_into_pts(line, display);
		free(line);
		line = get_next_line(fd);
	}
}
