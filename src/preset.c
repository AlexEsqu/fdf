/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:21:22 by alex              #+#    #+#             */
/*   Updated: 2024/10/28 18:00:05 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

/* Converting to isometric top down */
void	isometrify(t_display *display)
{
	display->angle_x_axis = 0.955316618;
	display->angle_y_axis = 0;
	display->angle_z_axis = PI * 45.0 / 180.0;
}

void	oblique(t_display *display)
{
	display->angle_x_axis = PI * 45.0 / 180.0;
	display->angle_y_axis = 0;
	display->angle_z_axis = PI * 45.0 / 180.0;
}

void	military(t_display *display)
{
	display->angle_x_axis = 0;
	display->angle_y_axis = 0;
	display->angle_z_axis = PI * 30.0 / 180.0;
}

void	top_view(t_display *display)
{
	display->angle_x_axis = 0.0;
	display->angle_y_axis = 0.0;
	display->angle_z_axis = 0.0;
}

void	front_view(t_display *display)
{
	display->angle_x_axis = 90 * PI_BY_180;
	display->angle_y_axis = 0.0;
	display->angle_z_axis = 0.0;
}
