/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:19 by mkling            #+#    #+#             */
/*   Updated: 2024/10/22 19:42:30 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	rotate_left(t_point point, t_display *display)
{
	float	cx;
	float	cy;
	float	cos_rot;
	float	sin_rot;
	float	rx;
	float	ry;

	fprintf(stderr, "point (%d, %d, %d) ", point.x, point.y, point.z);
	cx = point.x - display->grid->width;
	cy = point.y - display->grid->height;
	cos_rot = cos(display->alpha);
	sin_rot = sin(display->alpha);
	rx = (cx * cos_rot) - (cy * sin_rot);
	ry = (cx * cos_rot) + (cy * sin_rot);
	point.x = (rx - ry) * display->zoom;
	point.y = (rx + ry) * display->zoom;
	point.z = -(rx + ry);
	fprintf(stderr, "is (%d, %d, %d)\n", point.x, point.y, point.z);
	return (point);
}

void	rotate(t_display *display)
{
	int	i;

	i = 0;
	while (i < display->grid->pts_count)
	{
		display->grid->pts_array[i] = rotate_left(display->grid->pts_array[i], display);
		i++;
	}
	render(display);
}

void	origin_at_center_grid(t_point *point, t_display *display)
{
	point->x -= display->grid->width / 2;
	point->y -= display->grid->height / 2;
}

void	apply_zoom(t_point *point, t_display *display)
{
	point->x *= display->zoom;
	point->y *= display->zoom;
	point->z *= display->zoom;
}

void	center(t_point *point, t_display *display)
{
	point->x += display->offset_x;
	point->y += display->offset_y;
}

t_point	apply_zoom_and_offset(t_point *point, t_display *display)
{
	origin_at_center_grid(point, display);
	apply_zoom(point, display);
	center(point, display);
	return (*point);
}
