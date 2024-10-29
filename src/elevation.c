/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:03:29 by mkling            #+#    #+#             */
/*   Updated: 2024/10/29 14:40:35 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	find_highest_lowest_z(t_display *display, float *max_z, float *min_z)
{
	int	index;

	index = 0;
	*max_z = display->world->pts_array[index].z;
	*min_z = display->world->pts_array[index].z;
	while (index < display->grid_point_count)
	{
		if (display->world->pts_array[index].z > *max_z)
			*max_z = display->world->pts_array[index].z;
		if (display->world->pts_array[index].z < *min_z)
			*min_z = display->world->pts_array[index].z;
		index++;
	}
}

float	elevation_percentage(float z, float highest_z, float lowest_z)
{
	return ((z - lowest_z) / (highest_z - lowest_z));
}

void	assign_color_by_height(t_display *display)
{
	int		index;
	float	max_z;
	float	min_z;

	if (display->color_mode == 0)
		return ;
	find_highest_lowest_z(display, &max_z, &min_z);
	index = 0;
	if (max_z == min_z)
		assign_color_by_index(display);
	else
	{
		while (index < display->grid_point_count)
		{
			display->world->pts_array[index].rgb
				= interpolate_rgb_gradient(gradient_start(display->color_mode),
					gradient_end(display->color_mode),
					elevation_percentage(display->world->pts_array[index].z,
						max_z, min_z));
			index++;
		}
	}
}

void	add_elevation(t_display *display)
{
	int	index;

	index = 0;
	while (index < display->grid_point_count)
	{
		display->world->pts_array[index].z *= display->elevation;
		index++;
	}
	assign_color_by_height(display);
}
