/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 10:12:46 by cvermand          #+#    #+#             */
/*   Updated: 2018/05/10 10:24:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

unsigned int	merging(unsigned int a, unsigned int o,
		double alpha, double beta)
{
	double			r;
	double			g;
	double			b;

	r = (double)(a >> 16) / 255.0 * alpha +
		((double)(o >> 16) / 255.0) * (beta * (1.0 - alpha));
	g = (double)((a >> 8) & 0xff) / 255.0 * alpha +
		((double)((o >> 8) & 0xff) / 255.0) * (beta * (1.0 - alpha));
	b = (double)(a & 0xff) / 255 * alpha +
		((double)(o & 0xff) / 255) * (beta * (1.0 - alpha));
	return (rgb_to_hex(
				(int)round(r * 255), (int)round(g * 255), (int)round(b * 255)));
}

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int hex;

	hex = (r << 16) + (g << 8) + b;
	return (hex);
}

unsigned int	hsv_calculator(double hue, double saturation, double bright)
{
	double	c;
	double	m;
	double	x;
	int		cm;
	int		xm;

	c = bright * saturation;
	m = bright - c;
	x = c * (1.0 - fabs(fmod(hue / 60.0, 2) - 1.0));
	cm = (int)round((c + m) * 255);
	xm = (int)round((x + m) * 255);
	if (hue >= 0 && hue <= 60)
		return (rgb_to_hex(cm, xm, (int)round(m * 255)));
	if (hue > 60 && hue <= 120)
		return (rgb_to_hex(xm, xm, (int)round(m * 255)));
	if (hue > 120 && hue <= 180)
		return (rgb_to_hex((int)round(m * 255), cm, xm));
	if (hue > 180 && hue <= 240)
		return (rgb_to_hex((int)round(m * 255), xm, cm));
	if (hue > 240 && hue <= 300)
		return (rgb_to_hex(xm, (int)round(m * 255), cm));
	else
		return (rgb_to_hex(cm, (int)round((m) * 255), xm));
	return (0);
}
