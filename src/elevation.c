/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elevation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:03:29 by mkling            #+#    #+#             */
/*   Updated: 2024/10/28 18:17:48 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	find_highest_lowest_z(t_grid *grid, float *highest_z, float *lowest_z)
{
	int	index;

	index = 0;
	*highest_z = grid->pts_array[index].z;
	*lowest_z = grid->pts_array[index].z;
	while (index < grid->pts_count)
	{
		if (grid->pts_array[index].z > *highest_z)
			*highest_z = grid->pts_array[index].z;
		if (grid->pts_array[index].z < *lowest_z)
			*lowest_z = grid->pts_array[index].z;
		index++;
	}
}

float	find_elevation_percentage(float z, float highest_z, float lowest_z)
{
	return ((z - lowest_z) / (highest_z - lowest_z));
}

void	assign_color_by_height(t_display *display)
{
	int		index;
	float	highest_z;
	float	lowest_z;

	if (display->color_mode == 0)
		return ;
	highest_z = 0;
	lowest_z = 0;
	find_highest_lowest_z(display->world, &highest_z, &lowest_z);
	index = 0;
	while (index < display->world->pts_count)
	{
		display->world->pts_array[index].rgb
			= interpolate_rgb_gradient(gradient_start(display->color_mode),
				gradient_end(display->color_mode),
				find_elevation_percentage(display->world->pts_array[index].z,
					highest_z, lowest_z));
		index++;
	}
}

void	add_elevation(t_display *display)
{
	int	index;

	index = 0;
	while (index < display->world->pts_count)
	{
		display->world->pts_array[index].z *= display->elevation;
		index++;
	}
	assign_color_by_height(display);
}
