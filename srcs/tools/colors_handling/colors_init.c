/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:20:37 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 00:31:44 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

t_rgb			rgb_init(int value)
{
	t_rgb		rgb;
	int			r;
	int			g;
	int			b;

	r = (value & 0xff0000) >> 16;
	g = (value & 0xff00) >> 8;
	b = value & 0xff;
	rgb.r = (float)r / 255.0;
	rgb.g = (float)g / 255.0;
	rgb.b = (float)b / 255.0;
	rgb.value = value;
	return (rgb);
}

static int		clampi(int toclamp, int inf, int sup)
{
	if (toclamp < inf)
		return (inf);
	if (toclamp > sup)
		return (sup);
	return (toclamp);
}

void			rgb_updatevalue(t_rgb *rgb)
{
	int			r;
	int			g;
	int			b;

	r = clampi((int)roundf(rgb->r * 255), 0, 255);
	g = clampi((int)roundf(rgb->g * 255), 0, 255);
	b = clampi((int)roundf(rgb->b * 255), 0, 255);
	rgb->value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int				rgb_getvalue(t_rgb rgb)
{
	int			r;
	int			g;
	int			b;
	int			value;

	r = clampi((int)roundf(rgb.r * 255), 0, 255);
	g = clampi((int)roundf(rgb.g * 255), 0, 255);
	b = clampi((int)roundf(rgb.b * 255), 0, 255);
	value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (value);
}
