/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorconversion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 22:05:42 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 17:59:57 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_color			color_init_hsl(int color)
{
	t_color		finalcolor;

	finalcolor.type.hsl = rgb_to_hsl(color);
	finalcolor.rgb = int_to_rgb(color);
	return (finalcolor);
}

t_color			color_init_hsv(int color)
{
	t_color		finalcolor;

	finalcolor.type.hsv = rgb_to_hsv(color);
	finalcolor.rgb = int_to_rgb(color);
	return (finalcolor);
}
#include <stdio.h>
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

	//printf("BEFORE RGB : (%hhd, %hhd, %hhd)\n", r, g, b);
	result = r;
	result = (result << 8) + g;
	result = (result << 8) + b;
	//printf("HEX : %#x\n", result);
	return (result);
}

int				rgb_to_int(t_rgb rgb)
{
	return (get_rgb(rgb.r, rgb.g, rgb.b));
}

int				get_closestcolor_hsl(t_color *color)
{
	t_hsl		hsl;

	hsl.h = color->type.hsl.h;
	hsl.s = 100;
	hsl.l = 50;
	return (hsl_to_rgb(hsl));
}
int				get_closestcolor_hsv(t_color *color)
{
	t_hsv		hsv;

	hsv.h = color->type.hsv.h;
	hsv.s = 100;
	hsv.v = 100;
	return (hsv_to_rgb(hsv));
}
