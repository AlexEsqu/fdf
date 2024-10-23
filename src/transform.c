/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:19 by mkling            #+#    #+#             */
/*   Updated: 2024/10/23 13:25:37 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	isometrify(t_point point)
{
	int	tmp;

	tmp = point.x;
	point.x = (tmp - point.y) * cos(PI_BY_SIX);
	point.y = (tmp + point.y) * sin(PI_BY_SIX) - point.z;
	return (point);
}

void	rotate_z_axis(t_display *display)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < display->grid->pts_count)
	{
		tmp = display->grid->pts_array[i].x;
		display->grid->pts_array[i].x = tmp * cos(display->gamma)
			- display->grid->pts_array[i].y * sin(display->gamma);
		display->grid->pts_array[i].y = tmp * sin(display->gamma)
			+ display->grid->pts_array[i].y * cos(display->gamma);
		i++;
	}
	render(display);
}

void	rotate_y_axis(t_display *display)
{
	int		i;
	int		tmp;

	i = 0;
	while (i < display->grid->pts_count)
	{
		tmp = display->grid->pts_array[i].x;
		display->grid->pts_array[i].x = tmp * cos(display->tetha)
			- display->grid->pts_array[i].z * sin(display->tetha);
		display->grid->pts_array[i].z = display->grid->pts_array[i].z
			* cos(display->tetha) - tmp * cos(display->tetha);
		i++;
	}
	render(display);
}

// void	rotate_x_axis(t_display *display)
// {
// 	int		i;
// 	int		tmp;

// 	i = 0;
// 	while (i < display->grid->pts_count)
// 	{
// 		tmp = display->grid->pts_array[i].y;
// 		display->grid->pts_array[i].y = tmp * cos(display->alpha)
// 			- display->grid->pts_array[i].z * sin(display->alpha);
// 		display->grid->pts_array[i].z = tmp * sin(display->alpha)
// 			+ display->grid->pts_array[i].z * cos(display->alpha);
// 		i++;
// 	}
// 	render(display);
// }
/*
Generate a rotation matrix on the x axis such as
[ 1............0...................0...........]
[ 0.....cos(angle)...-sin(angle).]
[ 0.....sin(angle)....cos(angle).]
*/
void	generate_rotation_matrix_x(double angle, double matrix[3][3])
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cos(angle);
	fprintf(stderr, "Cosining cos(%f) = %f,", angle, matrix[1][1]);
	matrix[1][2] = -sin(angle);
	matrix[2][0] = 0;
	matrix[2][1] = sin(angle);
	matrix[2][2] = cos(angle);
	fprintf(stderr, "Generated matrix (%f, %f, %f)", matrix[0][0], matrix[0][1], matrix[0][2]);
	fprintf(stderr, "(%f, %f, %f)", matrix[1][0], matrix[1][1], matrix[1][2]);
	fprintf(stderr, "(%f, %f, %f)\n\n", matrix[2][0], matrix[2][1], matrix[2][2]);
}

/*
Generate a rotation matrix on the y axis such as
[ cos(angle)........0......sin(angle)]
[ 0.........................1............0.........]
[ -sin(angle)........0.....cos(angle)]
*/
void	generate_rotation_matrix_y(double angle, double matrix[3][3])
{
	matrix[0][0] = cos(angle);
	matrix[0][1] = 0;
	matrix[0][2] = sin(angle);
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sin(angle);
	matrix[2][1] = 0;
	matrix[2][2] = cos(angle);
	fprintf(stderr, "Generated matrix (%f, %f, %f)", matrix[0][0], matrix[0][1], matrix[0][2]);
	fprintf(stderr, "(%f, %f, %f)", matrix[1][0], matrix[1][1], matrix[1][2]);
	fprintf(stderr, "(%f, %f, %f)\n", matrix[2][0], matrix[2][1], matrix[2][2]);
}

t_point	multiply_by_matrix(t_point point, double matrix[3][3])
{
	t_point	result;

	fprintf(stderr, "point (%d, %d, %d) ", point.x, point.y, point.z);
	result.x = point.x * matrix[0][0]
		+ point.y * matrix[0][1]
		+ point.z * matrix[0][2];
	result.y = point.x * matrix[1][0]
		+ point.y * matrix[1][1]
		+ point.z * matrix[1][2];
	result.z = point.x * matrix[2][0]
		+ point.y * matrix[2][1]
		+ point.z * matrix[2][2];
	fprintf(stderr, "matrixed is (%d, %d, %d)\n", result.x, result.y, result.z);
	return (result);
}

void	rotate_x_axis(t_display *display)
{
	int		index;
	double	matrix[3][3];
	t_grid	*grid;

	grid = display->grid;
	index = grid->pts_count - 1;
	generate_rotation_matrix_x(display->tetha, matrix);
	while (index > 0)
	{
		multiply_by_matrix(grid->pts_array[index], matrix);
		index--;
	}
}

void	subtract(t_point *point, t_display *display)
{
	point->x = point->x - (display->grid->width - 1);
	point->y = point->y - (display->grid->height - 1);
}

void	scale(t_point *point, t_display *display)
{
	point->x = display->unit * point->x;
	point->y = display->unit * point->y;
}

void	zoom(t_point *point, t_display *display)
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
/*
For point i and j ;
For x_m the middle of the x axis and y_m the middle of the y axis ;
For a the zoom factor ;
For W the width of the window and H the height of the window ;
(a(i - x_m)+ W/2, a(j - y_m) + H /2)
*/
t_point	apply_zoom_and_offset(t_point *point, t_display *display)
{
	subtract(point, display);
	scale(point, display);
	zoom(point, display);
	center(point, display);
	return (*point);
}

// t_point	apply_zoom_and_offset(t_point *point, t_display *display)
// {
// 	origin_at_center_grid(point, display);
// 	apply_zoom(point, display);
// 	center(point, display);
// 	return (*point);
// }

// t_point	apply_zoom_and_offset(t_point *point, t_display *display)
// {
// 	subtract(point, display);
// 	// fprintf(stderr, "subtracted (%d, %d, %d)\n", point->x, point->y, point->z);
// 	scale(point, display);
// 	// fprintf(stderr, "scaled (%d, %d, %d)\n", point->x, point->y, point->z);
// 	zoom(point, display);
// 	// fprintf(stderr, "zoomed (%d, %d, %d)\n\n", point->x, point->y, point->z);
// 	center(point, display);
// 	// fprintf(stderr, "centered (%d, %d, %d)\n", point->x, point->y, point->z);
// 	return (*point);
// }
