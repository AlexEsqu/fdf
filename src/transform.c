/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:54:19 by mkling            #+#    #+#             */
/*   Updated: 2024/10/26 16:11:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* Put the origin of the vector at center of grid */
void	subtract_grid_center(t_point *point, t_display *display)
{
	point->x = point->x - (display->world->width) / 2;
	point->y = point->y - (display->world->height) / 2;
}

void	add_grid_center(t_point *point, t_display *display)
{
	point->x = point->x + (display->world->width) / 2;
	point->y = point->y + (display->world->height) / 2;
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
	zoom(point, display);
	center(point, display);
	return (*point);
}

void	isometrify(t_display *display)
{
	display->angle_x_axis = 45 * PI_BY_180;
	display->angle_y_axis = 35.264 * PI_BY_180;
	display->angle_z_axis = 0;
}

void	flatten(t_display *display)
{
	display->angle_x_axis = 0;
	display->angle_y_axis = 0;
	display->angle_z_axis = 0;
}

/*
Generate a rotation matrix on the x axis such as
[ 1 & 0 & 0 ]
[ 0 & cos(angle) & -sin(angle) ]
[ 0 & sin(angle) & cos(angle) ]
*/
void	generate_rotation_matrix_x(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cosinus;
	matrix[1][2] = -sinus;
	matrix[2][0] = 0;
	matrix[2][1] = sinus;
	matrix[2][2] = cosinus;
}

/*
Generate a rotation matrix on the y axis such as
[ cos(angle) & 0 & sin(angle)]
[ 0 & 1 & 0]
[ -sin(angle) & 0 & cos(angle)]
*/
void	generate_rotation_matrix_y(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = cosinus;
	matrix[0][1] = 0;
	matrix[0][2] = sinus;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sinus;
	matrix[2][1] = 0;
	matrix[2][2] = cosinus;
}

/*
Generate a rotation matrix on the z axis such as
[ cos(angle) & -sin(angle) & 0 ]
[ sin(angle) & cos(angle) & 0 ]
[ 0 & 0 & 1 ]
*/
void	generate_rotation_matrix_z(float angle, float matrix[3][3])
{
	float	cosinus;
	float	sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	matrix[0][0] = cosinus;
	matrix[0][1] = -sinus;
	matrix[0][2] = 0;
	matrix[1][0] = sinus;
	matrix[1][1] = cosinus;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	multiply_by_matrix(t_point *point, float matrix[3][3])
{
	t_point	result;

	result.x = point->x * matrix[0][0]
		+ point->y * matrix[0][1]
		+ point->z * matrix[0][2];
	result.y = point->x * matrix[1][0]
		+ point->y * matrix[1][1]
		+ point->z * matrix[1][2];
	result.z = point->x * matrix[2][0]
		+ point->y * matrix[2][1]
		+ point->z * matrix[2][2];
	point->x = result.x;
	point->y = result.y;
	point->z = result.z;
}

void	rotate(t_display *display)
{
	int		index;
	float	matrix_x[3][3];
	float	matrix_y[3][3];
	float	matrix_z[3][3];

	index = display->world->pts_count - 1;
	generate_rotation_matrix_x(display->angle_x_axis, matrix_x);
	generate_rotation_matrix_y(display->angle_y_axis, matrix_y);
	generate_rotation_matrix_z(display->angle_z_axis, matrix_z);
	while (index >= 0)
	{
		subtract_grid_center(&display->world->pts_array[index], display);
		multiply_by_matrix(&display->world->pts_array[index], matrix_x);
		multiply_by_matrix(&display->world->pts_array[index], matrix_y);
		multiply_by_matrix(&display->world->pts_array[index], matrix_z);
		add_grid_center(&display->world->pts_array[index], display);
		index--;
	}
}


