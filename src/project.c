/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:34 by mkling            #+#    #+#             */
/*   Updated: 2024/10/22 18:17:00 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_point	isometrify(t_point point)
{
	int	tmp;

	tmp = point.x;
	point.x = (tmp - point.y) * cos(0.523599);
	point.y = (tmp + point.y) * sin(0.523599) - point.z;
	return (point);
}

void	print_line(t_line *line, t_display *display)
{
	while (line->origin.x <= WIN_WIDTH && line->origin.y <= WIN_HEIGHT
		&& line->origin.x >= 0 && line->origin.y >= 0)
	{
		put_point(display, line->origin);
		line->error2 = 2 * line->error;
		if (line->error2 >= line->delta.y)
		{
			if (line->origin.x == line->end.x)
				break ;
			line->error += line->delta.y;
			line->origin.x += line->sign.x;
		}
		if (line->error2 <= line->delta.x)
		{
			if (line->origin.y == line->end.y)
				break ;
			line->error += line->delta.x;
			line->origin.y += line->sign.y;
		}
	}
}

void	plot_line(t_point origin, t_point end, t_display *display)
{
	t_line	line;

	// fprintf(stderr, "initial:\t{%d, %d} and {%d, %d}\n", origin.x, origin.y, end.x, end.y);
	line.origin = apply_zoom_and_offset(&origin, display);
	line.end = apply_zoom_and_offset(&end, display);
	// fprintf(stderr, "zoomed:\t\t{%d, %d} and {%d, %d}\n", origin.x, origin.y, end.x, end.y);
	line.origin = isometrify(line.origin);
	line.end = isometrify(line.end);
	// fprintf(stderr, "isometrized:\t{%d, %d} and {%d, %d}\n", line.origin.x, line.origin.y, line.end.x, line.end.y);
	line.sign.x = 1;
	line.sign.y = 1;
	line.delta.x = ft_abs(line.end.x - line.origin.x);
	if (line.origin.x > line.end.x)
		line.sign.x = -1;
	line.delta.y = -ft_abs(line.end.y - line.origin.y);
	if (line.origin.y > line.end.y)
		line.sign.y = -1;
	line.error = line.delta.x + line.delta.y;
	print_line(&line, display);
}



