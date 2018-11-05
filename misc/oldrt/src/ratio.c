/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:08:01 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 20:19:02 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_screen_ratio(t_scr *scr)
{
	if (scr->width >= scr->height)
	{
		scr->ratio_x = (double)scr->width / (double)scr->height;
		scr->ratio_y = 1;
	}
	else
	{
		scr->ratio_x = 1;
		scr->ratio_x = (double)scr->height / (double)scr->width;
	}
}


double		scale_screen_y(t_scr *scr, int y)
{
	static double discriminant = 0;
	double real_y;

	if (!discriminant)
		discriminant = (0.5 * scr->zoom * scr->height);

	real_y = 0 - (scr->ratio_y * ((y - scr->half_height)
				/ discriminant));
	return (real_y);
}

double		scale_screen_x(t_scr *scr, int x)
{
	static double discriminant = 0;
	double real_x;

	if (!discriminant)
		discriminant = (0.5 * scr->zoom * scr->width);
	real_x = scr->ratio_x * ((x - scr->half_width) / discriminant);	return (real_x);
}


int			reverse_scale_screen_x(t_scr *scr, double x)
{
	double pixel_x;

	pixel_x = ((x *
				(0.5 * scr->width * scr->zoom)) / scr->ratio_x)
				+ (scr->width * 0.5);
	return ((int)round(pixel_x));
}

int			reverse_scale_screen_y(t_scr *scr, double y)
{
	double pixel_y;

	pixel_y = (scr->height * 0.5) - y *
		((0.5 * scr->zoom * scr->height) / scr->ratio_y);
	return ((int)round(pixel_y));
}

int			get_pixel_index(int pixel_x, int pixel_y)
{
	return ((int)round(pixel_y) * WIDTH_SCREEN) + (int)round(pixel_x);
}
