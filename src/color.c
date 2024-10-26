/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:14:03 by mkling            #+#    #+#             */
/*   Updated: 2024/10/26 16:34:04 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	get_red(int color)
{
	return ((color >> 16) & 0xFF);
}

int	get_green(int color)
{
	return ((color >> 8) & 0xFF);
}

int	get_blue(int color)
{
	return (color & 0xFF);
}

int	encode_rgb(t_byte red, t_byte green, t_byte blue)
{
	return (red << 16 | green << 8 | blue);
}

void	extract_color(t_point *point, char *hexacode)
{
	if (ft_strchr(hexacode, 'A') || ft_strchr(hexacode, 'B')
		|| ft_strchr(hexacode, 'C') || ft_strchr(hexacode, 'D')
		|| ft_strchr(hexacode, 'E') || ft_strchr(hexacode, 'F'))
		point->rgb = ft_atoi_base(hexacode, HEXADECIMAL);
	else
		point->rgb = ft_atoi_base(hexacode, SMOLHEXADEC);
	// set_hsv(point);
}


/* DEBUG PRINTS */
/*
fprintf(stderr, "point (%d, %d, %d) has color %#x (h: %d, s: %d, v: %d)\n",
		point->x, point->y, point->z, point->rgb, point->hsv.hue,
		point->hsv.saturation, point->hsv.value);
*/
