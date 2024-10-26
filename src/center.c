/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:17:08 by alex              #+#    #+#             */
/*   Updated: 2024/10/26 16:24:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* Put the origin of the vector at center of grid */
void	subtract_grid_center(t_point *point, t_display *display)
{
	point->x = point->x - (display->world->width) / 2;
	point->y = point->y - (display->world->height) / 2;
}

/* Put the origin of the vector at top left of grid */
void	add_grid_center(t_point *point, t_display *display)
{
	point->x = point->x + (display->world->width) / 2;
	point->y = point->y + (display->world->height) / 2;
}

/* Set distance between each points */
void	scale(t_point *point, t_display *display)
{
	point->x = display->unit * point->x;
	point->y = display->unit * point->y;
	point->x *= display->zoom;
	point->y *= display->zoom;
	point->z *= display->zoom;
}

/* Center the grid representation in screen window */
void	center(t_point *point, t_display *display)
{
	point->x += display->offset_x;
	point->y += display->offset_y;
}

/*
For point x and y ;
For x_m the middle of the grid width and y_m the middle of the grid height ;
For a the zoom factor ;
For W the width of the window and H the height of the window ;
(a(i - x_m)+ W/2, a(j - y_m) + H /2)
*/
t_point	apply_zoom_and_offset(t_point *point, t_display *display)
{
	subtract_grid_center(point, display);
	scale(point, display);
	center(point, display);
	return (*point);
}
