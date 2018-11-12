/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversionhsl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 23:19:38 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/12 02:10:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_hsl			rgb_to_hsl(int color)
{
	t_hsl	hsl;
	float	max;
	float	min;
	t_rgb	rgb;

	rgb.r = (float)int_to_rgb(color).r / 255 * 100;
	rgb.g = (float)int_to_rgb(color).g / 255 * 100;
	rgb.b = (float)int_to_rgb(color).b / 255 * 100;
	max = ft_max(rgb.r, rgb.g, rgb.b);
	min = ft_min(rgb.r, rgb.g, rgb.b);
	hsl.l = (max + min) / 2.0;
	if (max == min)
	{
		hsl.s = 0;
		hsl.h = 0;
	}
	else {
		if (light < 0.5)
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
	return hsl;
}

int			hsl_to_rgb(t_hsl hsl)
{
	float	c;
	float	h;
	float	x;
	float	m;
//C = (1 - |2L - 1|) × S
//
//X = C × (1 - |(H / 60°) mod 2 - 1|)
//
//m = L - C/2
	c = (1 - fabs(2 * hsl.l - 1) * hsl.s);
	x = c * (1  - fabs(fmod(hsl.h / 60.0), 2) - 1);
	m = hsl.l - c / 2.0;

}

