/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:14:03 by mkling            #+#    #+#             */
/*   Updated: 2024/10/26 14:30:56 by alex             ###   ########.fr       */
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

/* Set HSV values from the RGB integer
Divide RGB red, green and blue value by 255
Find maximum, minimum, delta = (maximum value - minimum value)

HUE (°)
if delta == 0
__Hue = 0
if max value == red
__Hue = 60° * ( (green - blue) / delta ) % 6)
if max value == green
__Hue = 60° * ( (blue - red) / delta ) + 2)
if max value == blue
__Hue = 60° * ( (red - green) / delta ) + 4)

SATURATION (%)
if max value == 0
__Saturation = 0
else
__Saturation = delta / max value

VALUE (%)
Value = max value out of RED, GREEN or BLUE
*/
void	set_hsv(t_point *point)
{
	float	red;
	float	green;
	float	blue;
	float	delta;

	red = get_red(point->rgb) / 255.0;
	green = get_green(point->rgb) / 255.0;
	blue = get_blue(point->rgb) / 255.0;
	point->hsv.value = fmaxf(red, fmaxf(green, blue));
	delta = point->hsv.value - fminf(red, fminf(green, blue));
	if (delta == 0)
		point->hsv.hue = 0;
	else if (point->hsv.value == red)
		point->hsv.hue = 60 * fmodf(((green - blue) / delta), 6);
	else if (point->hsv.value == green)
		point->hsv.hue = 60 * (((blue - red) / delta) + 2);
	else
		point->hsv.hue = 60 * (((red - green) / delta) + 4);
	if (point->hsv.hue < 0)
		point->hsv.hue += 360;
	if (point->hsv.value == 0)
		point->hsv.saturation = 0;
	else
		point->hsv.saturation = delta / point->hsv.value;
}

/*Converts hsv values into an RGB integer
Find chroma (HSV value * HSV saturation), match (HSV value - chroma)
and X, a point on bottom of the RGB cube with same hue and chroma
Depending on the hue, find red, green and blue
Encode them as a RGB integer
*/
int	hsv_to_rgb(t_hsv hsv)
{
	float	chroma;
	float	x;
	float	m;

	chroma = hsv.value * hsv.saturation;
	x = chroma * (1 - fabsf(fmodf(hsv.hue / 60.0, 2) - 1));
	m = hsv.value - chroma;
	if (hsv.hue >= 0 && hsv.hue < 60)
		return (encode_rgb((t_byte)((chroma + m) * 255),
			(t_byte)((x + m) * 255), (t_byte)((0 + m) * 255)));
	else if (hsv.hue >= 60 && hsv.hue < 120)
		return (encode_rgb((t_byte)((x + m) * 255),
			(t_byte)((chroma + m) * 255), (t_byte)((0 + m) * 255)));
	else if (hsv.hue >= 120 && hsv.hue < 180)
		return (encode_rgb((t_byte)((0 + m) * 255),
			(t_byte)((chroma + m) * 255), (t_byte)((x + m) * 255)));
	else if (hsv.hue >= 180 && hsv.hue < 240)
		return (encode_rgb((t_byte)((x + m) * 255),
			(t_byte)((0 + m) * 255), (t_byte)((chroma + m) * 255)));
	else if (hsv.hue >= 240 && hsv.hue < 300)
		return (encode_rgb((t_byte)((x + m) * 255),
			(t_byte)((0 + m) * 255), (t_byte)((chroma + m) * 255)));
	else
		return (encode_rgb((t_byte)((chroma + m) * 255),
			(t_byte)((0 + m) * 255), (t_byte)((x + m) * 255)));
}

void	extract_color(t_point *point, char *hexacode)
{
	if (ft_strchr(hexacode, 'A') || ft_strchr(hexacode, 'B')
		|| ft_strchr(hexacode, 'C') || ft_strchr(hexacode, 'D')
		|| ft_strchr(hexacode, 'E') || ft_strchr(hexacode, 'F'))
		point->rgb = ft_atoi_base(hexacode, HEXADECIMAL);
	else
		point->rgb = ft_atoi_base(hexacode, SMOLHEXADEC);
	set_hsv(point);
	// fprintf(stderr, "point (%d, %d, %d) has color %#x (h: %f, s: %f, v: %f)\n",
	// 	point->x, point->y, point->z, point->rgb, point->hsv.hue,
	// 	point->hsv.saturation, point->hsv.value);
	// fprintf(stderr, "and back to rgb %#X\n", hsv_to_rgb(point->hsv));
}

int		interpolate_rgb_gradient(int start_rgb, int end_rgb, float progress)
{
	t_byte	red;
	t_byte	green;
	t_byte	blue;

	red = get_red(start_rgb);
	green = get_green(start_rgb);
	blue = get_blue(start_rgb);
	red = red + (get_red(end_rgb) - red) * progress;
	green = green + (get_green(end_rgb) - green) * progress;
	blue = blue + (get_blue(end_rgb) - blue) * progress;
	return (encode_rgb(red, green, blue));
}

void	assign_color(t_display *display)
{
	int		index;
	float	increment;

	if (!display->color_mode)
		return ;
	index = 0;
	increment = 1 / (float)(display->world->pts_count - 1);
	while (index < display->world->pts_count)
	{
		display->world->pts_array[index].rgb =
			interpolate_rgb_gradient(0x070000, 0x00ff60, index * increment);
		index++;
	}
}


/* DEBUG PRINTS */
/*
fprintf(stderr, "point (%d, %d, %d) has color %#x (h: %d, s: %d, v: %d)\n",
		point->x, point->y, point->z, point->rgb, point->hsv.hue,
		point->hsv.saturation, point->hsv.value);
*/
