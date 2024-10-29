/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkling <mkling@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 16:30:45 by alex              #+#    #+#             */
/*   Updated: 2024/10/29 14:37:55 by mkling           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	gradient_start(int color_mode)
{
	if (color_mode == 2)
		return (MATRIX_START);
	if (color_mode == 3)
		return (SUNSET_START);
	if (color_mode == 4)
		return (OCEAN_START);
	if (color_mode == 5)
		return (PURPLE_START);
	if (color_mode == 6)
		return (FLAME_START);
	if (color_mode == 7)
		return (COOL_START);
	if (color_mode == 8)
		return (EMERALD_START);
	if (color_mode == 9)
		return (SUNNY_START);
	else
		return (AUTUMN_START);
}

int	gradient_end(int color_mode)
{
	if (color_mode == 2)
		return (MATRIX_END);
	if (color_mode == 3)
		return (SUNSET_END);
	if (color_mode == 4)
		return (OCEAN_END);
	if (color_mode == 5)
		return (PURPLE_END);
	if (color_mode == 6)
		return (FLAME_END);
	if (color_mode == 7)
		return (COOL_END);
	if (color_mode == 8)
		return (EMERALD_END);
	if (color_mode == 9)
		return (SUNNY_END);
	else
		return (AUTUMN_END);
}

int	interpolate_rgb_gradient(int start_rgb, int end_rgb, float progress)
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

void	assign_color_by_index(t_display *display)
{
	int		index;
	float	increment;

	if (display->color_mode == 0)
		return ;
	index = 0;
	increment = 1 / (float)(display->grid_point_count - 1);
	while (index < display->grid_point_count)
	{
		display->world->pts_array[index].rgb
			= interpolate_rgb_gradient(gradient_start(display->color_mode),
				gradient_end(display->color_mode), index * increment);
		index++;
	}
}

// /* Set HSV values from the RGB integer
// Divide RGB red, green and blue value by 255
// Find maximum, minimum, delta = (maximum value - minimum value)

// HUE (°)
// if delta == 0
// __Hue = 0
// if max value == red
// __Hue = 60° * ( (green - blue) / delta ) % 6)
// if max value == green
// __Hue = 60° * ( (blue - red) / delta ) + 2)
// if max value == blue
// __Hue = 60° * ( (red - green) / delta ) + 4)

// SATURATION (%)
// if max value == 0
// __Saturation = 0
// else
// __Saturation = delta / max value

// VALUE (%)
// Value = max value out of RED, GREEN or BLUE
// */
// t_hsv	rgb_to_hsv(float red, float blue, float green)
// {
// 	float	delta;
// 	t_hsv	result;

// 	red = red / 255.0;
// 	green = green / 255.0;
// 	blue = blue / 255.0;
// 	result.value = fmaxf(red, fmaxf(green, blue));
// 	delta = result.value - fminf(red, fminf(green, blue));
// 	if (delta == 0)
// 		result.hue = 0;
// 	else if (result.value == red)
// 		result.hue = 60 * fmodf(((green - blue) / delta), 6);
// 	else if (result.value == green)
// 		result.hue = 60 * (((blue - red) / delta) + 2);
// 	else
// 		result.hue = 60 * (((red - green) / delta) + 4);
// 	if (result.hue < 0)
// 		result.hue += 360;
// 	if (result.value == 0)
// 		result.sat = 0;
// 	else
// 		result.sat = delta / result.value;
// 	return (result);
// }

// /*Converts hsv values into an RGB integer
// Find chroma (HSV value * HSV saturation), match (HSV value - chroma)
// and X, a point on bottom of the RGB cube with same hue and chroma
// Depending on the hue, find red, green and blue
// Encode them as a RGB integer
// */
// int	hsv_to_rgb(t_hsv hsv)
// {
// 	float	chroma;
// 	float	x;
// 	float	m;

// 	chroma = hsv.value * hsv.sat;
// 	x = chroma * (1 - fabsf(fmodf(hsv.hue / 60.0, 2) - 1));
// 	m = hsv.value - chroma;
// 	if (hsv.hue >= 0 && hsv.hue < 60)
// 		return (encode_rgb((t_byte)((chroma + m) * 255),
// 			(t_byte)((x + m) * 255), (t_byte)((0 + m) * 255)));
// 	else if (hsv.hue >= 60 && hsv.hue < 120)
// 		return (encode_rgb((t_byte)((x + m) * 255),
// 			(t_byte)((chroma + m) * 255), (t_byte)((0 + m) * 255)));
// 	else if (hsv.hue >= 120 && hsv.hue < 180)
// 		return (encode_rgb((t_byte)((0 + m) * 255),
// 			(t_byte)((chroma + m) * 255), (t_byte)((x + m) * 255)));
// 	else if (hsv.hue >= 180 && hsv.hue < 240)
// 		return (encode_rgb((t_byte)((x + m) * 255),
// 			(t_byte)((0 + m) * 255), (t_byte)((chroma + m) * 255)));
// 	else if (hsv.hue >= 240 && hsv.hue < 300)
// 		return (encode_rgb((t_byte)((x + m) * 255),
// 			(t_byte)((0 + m) * 255), (t_byte)((chroma + m) * 255)));
// 	else
// 		return (encode_rgb((t_byte)((chroma + m) * 255),
// 			(t_byte)((0 + m) * 255), (t_byte)((x + m) * 255)));
// }

// int	interpolate_hsv_gradient(int start_rgb, int end_rgb, float progress)
// {
// 	t_hsv	start;
// 	t_hsv	end;
// 	t_hsv	result;

// 	start = rgb_to_hsv((float)get_red(start_rgb),
// 			(float)get_green(start_rgb),
// 			(float)get_blue(start_rgb));
// 	end = rgb_to_hsv((float)get_red(end_rgb),
// 			(float)get_green(end_rgb),
// 			(float)get_blue(end_rgb));
// 	result.hue = start.hue + (end.hue - start.hue) * progress;
// 	result.sat = start.sat + (end.sat - start.sat) * progress;
// 	result.value = start.value + (end.value - start.value) * progress;
// 	return (hsv_to_rgb(result));
// }
