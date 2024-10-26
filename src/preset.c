/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:21:22 by alex              #+#    #+#             */
/*   Updated: 2024/10/26 17:14:32 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	isometrify(t_display *display)
{
	display->angle_x_axis = 45 * PI_BY_180;
	display->angle_y_axis = 35.5 * PI_BY_180;
	display->angle_z_axis = 0;
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

void	right_view(t_display *display)
{
	display->angle_x_axis = 0.0;
	display->angle_y_axis = 90 * PI_BY_180;
	display->angle_z_axis = -90 * PI_BY_180;
}
