/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:52:57 by mkling            #+#    #+#             */
/*   Updated: 2024/10/23 01:11:16 by mkling           ###   ########.fr       */
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
	fprintf(stderr, "clicked on %d, %d\n", x, y);
	return (0);
}

int	handle_input(int keysym, t_display *display)
{
	if (keysym == XK_Escape)
	{
		wipe(display);
		exit(0);
	}
	if (keysym == XK_Up)
	{
		display->zoom += 1;
		render(display);
	}
	if (keysym == XK_Down)
	{
		display->zoom -= 1;
		render(display);
	}
	if (keysym == XK_r)
	{
		display->alpha += PI_BY_180;
		rotate_z(display);
	}
	if (keysym == XK_p)
	{
		display->gamma += PI_BY_180;
		rotate_x(display);
	}
	if (keysym == XK_t)
	{
		display->tetha += PI_BY_180;
		rotate_y(display);
	}
	if (keysym == XK_a)
	{
		display->offset_y += 10;
		display->offset_x -= 10;
		render(display);
	}
	if (keysym == XK_d)
	{
		display->offset_y -= 10;
		display->offset_x += 10;
		render(display);
	}
	if (keysym == XK_s)
	{
		display->offset_x += 10;
		display->offset_y += 10;
		render(display);
	}
	if (keysym == XK_w)
	{
		display->offset_x -= 10;
		display->offset_y -= 10;
		render(display);
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}
