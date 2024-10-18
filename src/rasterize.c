/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:04:34 by mkling            #+#    #+#             */
/*   Updated: 2024/10/18 18:23:57 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_pts	make_pts_with_offset(t_pts *point, t_display *display)
{
	t_pts	new_point;

	new_point.x = point->x + display->zoom;
	new_point.y = point->y + display->zoom;
	new_point.z = point->z;
	new_point.color = point->color;
	return (new_point);
}

void	print_line(t_line *line, t_display *display)
{
	while (line->origin.x <= WIN_WIDTH && line->origin.y <= WIN_HEIGHT
		&& line->origin.x >= 0 && line->origin.y >= 0)
	{
		put_pixel(&display->img, line->origin.x, line->origin.y, 0xFFFFFF);
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

void	plot_line(t_pts *origin, t_pts *end, t_display *display)
{
	t_line	line;

	line.origin = make_pts_with_offset(origin, display);
	line.end = make_pts_with_offset(end, display);
	line.sign.x = 1;
	line.sign.y = 1;
	line.delta.x = ft_abs(line.end.x - line.origin.x);
	if (line.origin.x < line.end.x)
		line.sign.x = -1;
	line.delta.y = -ft_abs(line.end.y - line.origin.y);
	if (line.origin.y < line.end.y)
		line.sign.y = -1;
	line.error = line.delta.x + line.delta.y;
	print_line(&line, display);
}



// void	slope_less_than_one(t_pts *origin, t_pts *end, t_display *display)
// {
// 	int	p;
// 	int	i;

// 	i = 0;
// 	p = 2 * origin->dy - origin->dx;
// 	put_pixel(&display->img, origin->x, origin->y, origin->color);
// 	while (i < origin->dx)
// 	{
// 		origin->x += 1;
// 		if (p < 0)
// 			p = p + 2 * origin->dy;
// 		else
// 		{
// 			origin->y += 1;
// 			p = p + 2 * origin->dy - 2 * origin->dx;
// 		}
// 		put_pixel(&display->img, origin->x, origin->y, origin->color);
// 		i++;
// 	}
// }

// void	slope_more_than_one(t_pts *origin, t_pts *end, t_display *display)
// {
// 	int	p;
// 	int	i;

// 	i = 0;
// 	p = 2 * origin->dx - origin->dy;
// 	put_pixel(&display->img, origin->x, origin->y, origin->color);
// 	while (i < origin->dy)
// 	{
// 		origin->y += 1;
// 		if (p < 0)
// 			p = p + 2 * origin->dx;
// 		else
// 		{
// 			origin->x += 1;
// 			p = p + 2 * origin->dx - 2 * origin->dy;
// 		}
// 		put_pixel(&display->img, origin->x, origin->y, origin->color);
// 		i++;
// 	}
// }

// void	plot_line(t_pts *origin, t_pts *end, t_display *display)
// {
// 	origin->dx = end->x - origin->x;
// 	origin->dy = end->y - origin->y;
// 	if (ft_abs(origin->dx) > ft_abs(origin->dy))
// 		slope_less_than_one(origin, end, display);
// 	else
// 		slope_more_than_one(origin, end, display);
// }



