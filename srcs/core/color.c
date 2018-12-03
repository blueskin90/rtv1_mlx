/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 07:40:38 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 10:40:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			rgb_updatevalue(t_RGB *rgb)
{
	int			r;
	int			g;
	int			b;

	r = (int)roundf(rgb->r * 255);
	g = (int)roundf(rgb->g * 255);
	b = (int)roundf(rgb->b * 255);
	rgb->value = (r << 16) + (g << 8) + b;
}

t_RGB			rgb_mul_rgb(t_RGB a, t_RGB b)
{
	t_RGB		c;

	c.r = clampf(a.r * b.r, 0, 1);
	c.g = clampf(a.g * b.g, 0, 1);
	c.b = clampf(a.b * b.b, 0, 1);
	rgb_updatevalue(&c);
	return (c);
}

t_RGB			rgb_mul(t_RGB a, float scalar)
{
	t_RGB		b;

	b.r = clampf(a.r * scalar, 0, 1);
	b.g = clampf(a.g * scalar, 0, 1);
	b.b = clampf(a.b * scalar, 0, 1);
	rgb_updatevalue(&b);
	return (b);
}

t_RGB			rgb_add(t_RGB a, t_RGB b)
{
	t_RGB		c;

	c.r = clampf(a.r + b.r, 0, 1);
	c.g = clampf(a.g + b.g, 0, 1);
	c.b = clampf(a.b + b.b, 0, 1);
	rgb_updatevalue(&c);
	return (c);	
}

t_RGB			rgb_init(int value)
{
	t_RGB		rgb;
	int r;
	int g;
	int b;

	r = (value & 0xff0000) >> 16;
	g = (value & 0xff00) >> 8;
	b = value & 0xff;
	rgb.r = r / 255.0;
	rgb.g = g / 255.0;
	rgb.b = b / 255.0;
	rgb.value = value;
	return (rgb);
}
