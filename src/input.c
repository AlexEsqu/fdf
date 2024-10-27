/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:52:57 by mkling            #+#    #+#             */
/*   Updated: 2024/10/27 09:56:41 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(int button_or_key, t_display *display)
{
	if (button_or_key == WHEEL_UP || button_or_key == XK_Up)
		display->zoom *= 1.1;
	else
		display->zoom *= 0.9;
}

void	color_mode(int keysym, t_display *display)
{
	if (keysym == XK_b)
		display->color_mode = 0;
	if (keysym == XK_c)
	{
		if (display->color_mode < 9)
			display->color_mode++;
		else
			display->color_mode = 1;
	}
}

void	rotations(int keysym, t_display *display)
{
	if (keysym == XK_y)
		isometrify(display);
	if (keysym == XK_o)
		top_view(display);
	if (keysym == XK_l)
		front_view(display);
	if (keysym == XK_p)
		right_view(display);
	if (keysym == XK_r)
		display->angle_x_axis += 0.05;
	if (keysym == XK_f)
		display->angle_x_axis -= 0.05;
	if (keysym == XK_t)
		display->angle_z_axis += 0.05;
	if (keysym == XK_g)
		display->angle_z_axis -= 0.05;
	if (keysym == XK_Left)
		display->angle_y_axis += 0.05;
	if (keysym == XK_Right)
		display->angle_y_axis -= 0.05;
	if (keysym ==  XK_u)
		display->elevation += 0.2;
	if (keysym ==  XK_j)
		display->elevation -= 0.2;
}

int	handle_mouse(int button, int x, int y, t_display *display)
{
	if (button == WHEEL_UP || button == WHEEL_DOWN)
		zoom(button, display);
	if (button == LEFT_CLICK)
		mlx_string_put(display->link, display->window, x, y,
			WHITE, "Left Click");
	render(display);
	return (0);
}

int	handle_input(int keysym, t_display *display)
{
	rotations(keysym, display);
	color_mode(keysym, display);
	if (keysym == XK_Escape)
	{
		wipe(display);
		exit(0);
	}
	if (keysym == XK_Up)
		zoom(keysym, display);
	if (keysym == XK_Down)
		zoom(keysym, display);
	if (keysym == XK_a)
		display->offset_x -= 10;
	if (keysym == XK_d)
		display->offset_x += 10;
	if (keysym == XK_s)
		display->offset_y += 10;
	if (keysym == XK_w)
		display->offset_y -= 10;
	render(display);
	return (0);
}
