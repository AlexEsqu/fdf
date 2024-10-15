/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:19:45 by mkling            #+#    #+#             */
/*   Updated: 2024/10/15 17:33:28 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	open_file(char *map_filepath)
{
	int	fd;

	fd = open(map_filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("failed to open the map file\n", 2);
		exit(1);
	}
	return (fd);
}

void	check_syntax(char *word)
{
	int	i;

	i = 0;
	if (is_too_long_for_int(word))
	{
		ft_putstr_fd("map file contains incorrect values\n", 2);
		exit(1);
	}
	while (word[i])
	{
		if (word[i] != '\n' && (((word[0] == '0' && word[1] == 'x')
					&& !ft_isdigit_or_hexa(word[i])) || !ft_isdigit(word[i])))
		{
			ft_putstr_fd("map file contains non numbers\n", 2);
			exit(1);
		}
		i++;
	}
}

void	set_map_height_width(char *map_filepath, t_map *map)
{
	int		fd;
	int		line_count;
	char	*line;

	fd = open_file(map_filepath);
	line_count = 0;
	line = get_next_line(fd);
	map->column_count = countword(line, ' ');
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map->row_count = line_count;
}

int	*extract_into_int_array(char *line, int column_count)
{
	char	**split_line;
	int		*int_array;
	int		index;

	split_line = ft_split(line, ' ');
	int_array = ft_calloc(column_count + 1, sizeof(int));
	index = 0;
	while (split_line[index])
	{
		if (ft_strcmp(split_line[index], "\n") == 0)
			break ;
		check_syntax(split_line[index]);
		int_array[index] = ft_atoi(split_line[index]);
		index++;
	}
	ft_free_tab(split_line);
	return (int_array);
}

t_map	parse_map_into_array(char *map_filepath)
{
	int		fd;
	int		row;
	char	*line;
	t_map	map;

	set_map_height_width(map_filepath, &map);
	fd = open_file(map_filepath);
	map.matrix = ft_calloc((map.row_count + 1), sizeof(int *));
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		map.matrix[row] = extract_into_int_array(line, map.column_count);
		free(line);
		row++;
		line = get_next_line(fd);
	}
	return (map);
}
