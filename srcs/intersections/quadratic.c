/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:03:35 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:03:39 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				quadratic(float a, float b, float c, float l[2])
{
	float		d;

	if (a == 0.0)
		return (0);
	d = b * b - 4 * a * c;
	if (d < TOLERANCE)
		return (0);
	d = sqrtf(d);
	l[0] = (-b + d) / (2 * a);
	l[1] = (-b - d) / (2 * a);
	return (2);
}
