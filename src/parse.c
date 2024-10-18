/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:19:45 by mkling            #+#    #+#             */
/*   Updated: 2024/10/18 22:31:39 by mkling           ###   ########.fr       */
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
	grid->col_count = countword(line, ' ');
	while (line != NULL)
	{
		line_count++;
		check_syntax(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	grid->pts_count = 0;
	grid->row_count = line_count;
}

void	apply_zoom_and_offset(t_pts *point, t_display *display)
{
	// point->x -= display->grid->col_count - 1;
	// point->y -= display->grid->row_count - 1;
	point->x *= display->zoom;
	point->y *= display->zoom;
	point->z *= display->zoom;
	point->x += display->offset_x;
	point->y += display->offset_y;
}

t_pts	turn_into_pts(char *map_point, t_display *display)
{
	t_pts	point;
	char	**values;

	point.x = display->grid->pts_count / display->grid->col_count;
	point.y = display->grid->pts_count % display->grid->col_count;
	if (ft_strchr(map_point, ',') == 0)
	{
		point.z = ft_atoi(map_point);
		point.color = 0xffffff;
		fprintf(stderr, "made pts %d:\t(x:%d, y:%d, z:%d)\n",
			display->grid->pts_count, point.x, point.y, point.z);
		apply_zoom_and_offset(&point, display);
		fprintf(stderr, "made pts %d:\t(x:%d, y:%d, z:%d)\n",
			display->grid->pts_count, point.x, point.y, point.z);
		return (point);
	}
	values = ft_split(map_point, ',');
	point.z = ft_atoi(values[0]);
	point.color = ft_atoi(values[1]);
	apply_zoom_and_offset(&point, display);
	ft_free_tab(values);
	return (point);
}

void	split_line_into_pts(char *line, t_display *display)
{
	char	**split_line;
	int		index;

	split_line = ft_split(line, ' ');
	if (!split_line)
		error_exit("malloc error", display);
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

	display->offset_x = WIN_WIDTH / 2;
	display->offset_y = WIN_HEIGHT / 2;
	display->zoom = 15;
	display->grid = ft_calloc(1, sizeof(t_grid));
	check_grid_size_syntax(map_filepath, display->grid);
	fd = open_file(map_filepath);
	display->grid->pts_array = ft_calloc((display->grid->row_count
				* display->grid->col_count), sizeof(t_pts));
	index = 0;
	line = get_next_line(fd);
	while (line)
	{
		split_line_into_pts(line, display);
		free(line);
		line = get_next_line(fd);
	}
}
