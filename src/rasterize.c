/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:34 by mkling            #+#    #+#             */
/*   Updated: 2024/10/09 17:35:56 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	print_line(t_line *line, t_display *display)
{
	while (line->origin.x < WIN_WIDTH && line->origin.y < WIN_HEIGHT
		&& line->origin.x > 0 && line->origin.y > 0)
	{
		img_pixel_put(&display->img, line->origin.x, line->origin.y, 0x00FF00);
		line->error2 = 2 * line->error;
		if (line->error2 >= line->direction.y)
		{
			if (line->origin.x == line->end.x)
				break ;
			line->error += line->direction.y;
			line->origin.x += line->sign.x;
		}
		if (line->error2 <= line->direction.x)
		{
			if (line->origin.y == line->end.y)
				break ;
			line->error += line->direction.x;
			line->origin.y += line->sign.y;
		}
	}
}

void	plot_line(t_pts *origin, t_pts *end, t_display *display)
{
	t_line	line;

	line.origin = *origin;
	line.end = *end;
	line.sign.x = 1;
	line.sign.y = 1;
	line.direction.x = ft_abs(line.end.x - line.origin.x);
	if (line.origin.x < line.end.x)
		line.sign.x = -1;
	line.direction.y = -ft_abs(line.end.y - line.origin.y);
	if (line.origin.y < line.end.y)
		line.sign.y = -1;
	line.error = line.direction.x + line.direction.y;
	print_line(&line, display);
}



