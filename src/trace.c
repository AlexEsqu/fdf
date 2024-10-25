/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:34 by mkling            #+#    #+#             */
/*   Updated: 2024/10/25 10:56:38 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

float	calculate_line_length(t_point start, t_point end)
{
	return (sqrtf((end.x - start.x) * (end.x - start.x)
			+ (end.y - start.y) * (end.y - start.y)));
}

void	print_line(t_line *line, t_display *display)
{
	line->current = line->start;
	while (1)
	{
		line->current.rgb = interpolate_rgb_gradient(line, &line->current);
		put_point(display, line->current);
		line->error2 = 2 * line->error;
		if (line->error2 >= line->delta.y)
		{
			if (line->current.x == line->end.x)
				break ;
			line->error += line->delta.y;
			line->current.x += line->sign.x;
		}
		if (line->error2 <= line->delta.x)
		{
			if (line->current.y == line->end.y)
				break ;
			line->error += line->delta.x;
			line->current.y += line->sign.y;
		}
	}
}

void	plot_line(t_point start, t_point end, t_display *display)
{
	t_line	line;

	line.start = apply_zoom_and_offset(&start, display);
	line.end = apply_zoom_and_offset(&end, display);
	line.start = isometrify(line.start);
	line.end = isometrify(line.end);
	line.sign.x = 1;
	line.sign.y = 1;
	line.delta.x = ft_abs(line.end.x - line.start.x);
	if (line.start.x > line.end.x)
		line.sign.x = -1;
	line.delta.y = -ft_abs(line.end.y - line.start.y);
	if (line.start.y > line.end.y)
		line.sign.y = -1;
	line.error = line.delta.x + line.delta.y;
	line.length = calculate_line_length(line.start, line.end);
	print_line(&line, display);
}



