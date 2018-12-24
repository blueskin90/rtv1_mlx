/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:45:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 18:12:49 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		default_float(float number, float def)
{
	if (number == INFINITY)
		return (def);
	return (number);
}

t_vec		default_vec(t_vec vec, t_vec def)
{
	if (vec.x == INFINITY)
		vec.x = def.x;
	if (vec.y == INFINITY)
		vec.y = def.y;
	if (vec.z == INFINITY)
		vec.z = def.z;
	return (vec);
}

t_RGB		default_rgb(t_RGB rgb, t_RGB def)
{
	if (rgb.r == INFINITY)
		rgb.r = def.r;
	if (rgb.g == INFINITY)
		rgb.g = def.g;
	if (rgb.b == INFINITY)
		rgb.b = def.b;
	if (rgb.value == INFINITY)
		rgb.value = def.value;
	return (rgb);
}
