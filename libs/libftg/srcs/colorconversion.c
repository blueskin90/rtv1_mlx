/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:45:44 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 17:57:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

int			hsv_to_rgb(t_hsv hsv)
{
	float	c;
	float	h;
	float	x;
	float	m;

	c = (float)hsv.v / 100 * ((float)hsv.s / 100);
	h = (float)hsv.h / 60;
	x = c * (1 - fabsf(h - ((int)h / 2 * 2) - 1));
	m = (float)hsv.v / 100 - c;
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

t_hsv		rgb_to_hsv(int color)
{
	t_hsv	hsv;
	float	max;
	float	min;

	hsv.h = (float)int_to_rgb(color).r / 255 * 100;
	hsv.s = (float)int_to_rgb(color).g / 255 * 100;
	hsv.v = (float)int_to_rgb(color).b / 255 * 100;
	max = ft_max(hsv.h, hsv.s, hsv.v);
	min = ft_min(hsv.h, hsv.s, hsv.v);
	if (max == min)
		hsv.h = 0;
	else if (max == hsv.h)
		hsv.h = (int)round((60 * ((float)(hsv.s - hsv.v) / (max - min)) + 360))
			% 360;
	else if (max == hsv.s)
		hsv.h = round(60 * ((float)(hsv.v - hsv.h) / (max - min)) + 120);
	else
		hsv.h = round(60 * ((float)(hsv.h - hsv.s) / (max - min)) + 240);
	hsv.s = round((max == 0) ? 0 : (1 - (float)(min / max)) * 100);
	hsv.v = round(max);
	return (hsv);
}

void		modifyhue_hsv(int y, t_color *color)
{
	y = (y < 100) ? 100 : y;
	y = (y > 279) ? 279 : y;
	color->type.hsv.h = ((float)(279 - y) / 179 * 359);
	color->rgb.value = hsv_to_rgb(color->type.hsv);
	color->rgb = int_to_rgb(color->rgb.value);
}

void		modifysv(int x, int y, t_color *color)
{
	x = (x < 96) ? 96 : x;
	x = (x > 275) ? 275 : x;
	y = (y < 100) ? 100 : y;
	y = (y > 279) ? 279 : y;
	color->type.hsv.s = ((float)(x - 96) / 179 * 100);
	color->type.hsv.v = ((float)(279 - y) / 179 * 100);
	color->rgb.value = hsv_to_rgb(color->type.hsv);
	color->rgb = int_to_rgb(color->rgb.value);
}
