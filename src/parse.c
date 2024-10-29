/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:19:45 by mkling            #+#    #+#             */
/*   Updated: 2024/10/29 14:37:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	open_file(char *map_filepath, t_display *display)
{
	int	fd;

	fd = open(map_filepath, O_RDONLY);
	exit_if(fd < 0, "failed to open the map file\n", display);
	return (fd);
}

t_point	turn_into_pts(char *map_point, t_display *display)
{
	t_point	point;
	char	**values;

	point.y = display->grid_point_count / display->grid_width;
	point.x = fmod(display->grid_point_count, display->grid_width);
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
	exit_if((split_line == NULL), "Malloc error\n", display);
	index = 0;
	while (split_line[index])
	{
		display->local->pts_array[display->grid_point_count]
			= turn_into_pts(split_line[index], display);
		display->grid_point_count++;
		index++;
	}
	ft_free_tab(split_line);
}

void	parse_file_into_grid(char *map_filepath, t_display *display)
{
	int		fd;
	char	*line;

	display->local = ft_calloc(1, sizeof(t_grid));
	display->world = ft_calloc(1, sizeof(t_grid));
	exit_if((!display->local || !display->world),
		"Failed to allocate grid\n", display);
	init_angles_offsets(display);
	display->local->pts_array = ft_calloc((display->grid_height
				* display->grid_width), sizeof(t_point));
	display->world->pts_array = ft_calloc((display->grid_height
				* display->grid_width), sizeof(t_point));
	fd = open_file(map_filepath, display);
	line = get_next_line(fd);
	while (line)
	{
		split_line_into_pts(line, display);
		free(line);
		line = get_next_line(fd);
	}
}
