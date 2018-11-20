/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversionhsl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:19:38 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 19:33:13 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"
#include <stdio.h>
t_hsl			rgb_to_hsl(int color)
{
	t_hsl	hsl;
	float	max;
	float	min;
	float	r;
	float	g;
	float	b;

	r = (float)int_to_rgb(color).r / 255;
	g = (float)int_to_rgb(color).g / 255;
	b = (float)int_to_rgb(color).b / 255;
	printf("rgb : [%f][%f][%f]\n", r, g, b);
	max = (float)ft_max(r, g, b);
	min = (float)ft_min(r, g, b);
	printf("min : %f max : %f\n", min, max);
	hsl.l = (max + min) / 2.0;
	printf("l : %f\n", hsl.l);
	if (max == min)
	{
		hsl.s = 0;
		hsl.h = 0;
	}
	else {
		if (hsl.l == 1)
			hsl.s = 0;
		else
			hsl.s = (max - min) / (1 - (fabs(2 * hsl.l - 1)));
		if (r == max)
		{
			hsl.h = 60 * fmod(((g - b) / (max - min)), 6);
		}
		else if (g == max)
			hsl.h = 60 * (((b - r) / (max - min)) + 2);
		else 
			hsl.h = 60 * (((r - g) / (max - min)) + 4);
	}
	if (hsl.h < 0)
		hsl.h = 360 + hsl.h;
	//printf("h: %f s: %f l: %f\n", hsl.h, hsl.s, hsl.l);
	return hsl;
}

int			hsl_to_rgb(t_hsl hsl)
{
	float	c;
	float	h;
	float	x;
	float	m;

	c = (1.0 - fabs(2.0 * (float)hsl.l - 1.0) * (float)hsl.s);
	x = c * (1.0  - fabs(fmod((float)hsl.h / 60.0, 2.0) - 1.0));
	m = (float)hsl.l - c / 2.0;
	h = (float)hsl.h / 60;
//	printf("HSL : %f, %f, %f\n", hsl.h, hsl.s, hsl.l);
//	printf("c : %f, x : %f, m : %f, h : %f\n", c, x, m, h);
	if (h >= 0.0 && h < 1.0)
		return (get_rgb(round((c + m) * 255), round((x + m) * 255), round(m * 255)));
	if (h >= 1.0 && h < 2.0)
		return (get_rgb(round((x + m) * 255), round((c + m) * 255), round(m * 255)));
	if (h >= 2.0 && h < 3.0)
		return (get_rgb(round(m * 255), round((c + m) * 255), round((x + m) * 255)));
	if (h >= 3.0 && h < 4.0)
		return (get_rgb(round(m * 255), round((x + m) * 255), round((c + m) * 255)));
	if (h >= 4.0 && h < 5.0)
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
