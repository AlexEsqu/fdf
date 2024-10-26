/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:52:57 by mkling            #+#    #+#             */
/*   Updated: 2024/10/26 16:38:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	handle_mouse(int button, int x, int y, t_display *display)
{
	if (button == 1 && x > WIN_WIDTH - 20 && y < 100)
	{
		wipe(display);
		exit(0);
	}
	// fprintf(stderr, "clicked on %d, %d", x, y);
	return (0);
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
	render(display);
}

int	handle_input(int keysym, t_display *display)
{
	rotations(keysym, display);
	if (keysym == XK_Escape)
	{
		wipe(display);
		exit(0);
	}
	if (keysym == XK_Up)
		display->zoom += 1;
	if (keysym == XK_Down)
		display->zoom -= 1;
	if (keysym == XK_a)
		display->offset_x -= 10;
	if (keysym == XK_d)
		display->offset_x += 10;
	if (keysym == XK_s)
		display->offset_y += 10;
	if (keysym == XK_w)
		display->offset_y -= 10;
	if (keysym == XK_c)
		display->color_mode = !display->color_mode;
	render(display);
	return (0);
}
