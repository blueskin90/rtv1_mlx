/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 22:05:42 by toliver           #+#    #+#             */
/*   Updated: 2018/10/23 16:51:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			color_init(int color)
{
	t_color		finalcolor;

	finalcolor.hsv = rgb_to_hsv(color);
	finalcolor.rgb = int_to_rgb(color);
	return (finalcolor);
}

t_rgb			int_to_rgb(int c)
{
	t_rgb		rgb;

	rgb.r = c >> 16;
	rgb.g = (c >> 8) - ((c >> 16) * 0x100);
	rgb.b = c - ((c >> 8) * 0x100);
	rgb.value = c;
	return (rgb);
}

int				get_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	int			result;

	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	return (result);
}

int				rgb_to_int(t_rgb rgb)
{
	return (get_rgb(rgb.r, rgb.g, rgb.b));
}

int				get_closestcolor(t_color *color)
{
	t_hsv		hsv;

	hsv.h = color->hsv.h;
	hsv.s = 100;
	hsv.v = 100;
	return (hsv_to_rgb(hsv));
}
