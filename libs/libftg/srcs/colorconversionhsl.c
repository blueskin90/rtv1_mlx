/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversionhsl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:19:38 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 17:05:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"
#include <stdio.h>
t_hsl			rgb_to_hsl(int color)
{
	t_hsl	hsl;
	float	max;
	float	min;
	t_rgb	rgb;

	rgb.r = (float)int_to_rgb(color).r / 255;
	rgb.g = (float)int_to_rgb(color).g / 255;
	rgb.b = (float)int_to_rgb(color).b / 255;
	printf("rgb : [%d][%d][%d]\n", rgb.r, rgb.g, rgb.b);
	max = (float)ft_max(rgb.r, rgb.g, rgb.b);
	min = (float)ft_min(rgb.r, rgb.g, rgb.b);
	printf("min : %f max : %f\n", min, max);
	hsl.l = (max + min) / 2.0;
	printf("l : %f\n", hsl.l);
	if (max == min)
	{
		hsl.s = 0;
		hsl.h = 0;
	}
	else {
		if (hsl.l < 0.5)
			hsl.s = (max - min) / (max + min);
		else
			hsl.s = (max - min) / (2 - max - min);
		if (rgb.r == max)
		{
			hsl.h = 60 * (rgb.g - rgb.b) / (max - min);
			if (hsl.h < 0)
				hsl.h = 360 + hsl.h;
		}
		else if (rgb.g == max)
			hsl.h = 120 + 60 * (rgb.b - rgb.r) / (max - min);
		else 
			hsl.h = 240 + 60 * (rgb.r - rgb.g) / (max - min);
	}
	printf("h: %f s: %f l: %f\n", hsl.h, hsl.s, hsl.l);
	return hsl;
}

int			hsl_to_rgb(t_hsl hsl)
{
	float	c;
	float	h;
	float	x;
	float	m;

	c = (1 - fabs(2 * (float)hsl.l - 1) * (float)hsl.s);
	x = c * (1  - fabs(fmod((float)hsl.h / 60.0, 2)) - 1);
	m = (float)hsl.l - c / 2.0;
	h = (float)hsl.h / 60;
	if (h >= 0 && h < 1)
		return (get_rgb(round((c + m) * 255), round((x + m) * 255), round(m * 255)));
	if (h >= 1 && h < 2)
		return (get_rgb(round((x + m) * 255), round((c + m) * 255), round(m * 255)));
	if (h >= 2 && h < 3)
		return (get_rgb(round(m * 255), round((c + m) * 255), round((x + m) * 255)));
	if (h >= 3 && h < 4)
		return (get_rgb(round(m * 255), round((x + m) * 255), round((c + m) * 255)));
	if (h >= 4 && h < 5)
		return (get_rgb(round((x + m) * 255), round(m * 255), round((c + m) * 255)));
	return (get_rgb(round((c + m) * 255), round(m * 255), round((x + m) * 255)));
}

void		modifyhue_hsl(int y, t_color *color)
{
	y = (y < 100) ? 100 : y;
	y = (y > 279) ? 279 : y;
	color->type.hsl.h = ((float)(279 - y) / 179 * 359);
	color->rgb.value = hsl_to_rgb(color->type.hsl);
	color->rgb = int_to_rgb(color->rgb.value);
}

void		change_hsl(t_color	*color, float h, float s, float l)
{
	color->type.hsl.h = h;
	color->type.hsl.s = s;
	color->type.hsl.l = l;
	color->rgb.value = hsl_to_rgb(color->type.hsl);
	color->rgb = int_to_rgb(color->rgb.value);
}
// a quoi sert cette fonction
void		modifyhsl(int x, int y, t_color *color)
{
		// PAS JUSTE
	x = (x < 96) ? 96 : x;
	x = (x > 275) ? 275 : x;
	y = (y < 100) ? 100 : y;
	y = (y > 279) ? 279 : y;
	color->type.hsl.s = ((float)(x - 96) / 179 * 100);
	color->type.hsl.l = ((float)(279 - y) / 179 * 100);
	color->rgb.value = hsl_to_rgb(color->type.hsl);
	color->rgb = int_to_rgb(color->rgb.value);
}
