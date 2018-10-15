/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 06:15:34 by toliver           #+#    #+#             */
/*   Updated: 2018/10/15 06:15:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		vector_cos(t_vector a, t_vector b)
{
	return (vector_dotproduct(a, b) / (vector_magnitude(a)
				* vector_magnitude(b)));
}

float		vector_dotproduct(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vector_div(t_vector a, float s)
{
	t_vector	b;

	if (s == 0.0)
		return (a);
	b.x = a.x / s;
	b.y = a.y / s;
	b.z = a.z / s;
	b.w = 0;
	return (b);
}

t_vector	vector_opposite(t_vector a)
{
	t_vector	b;

	b.x = -a.x;
	b.y = -a.y;
	b.z = -a.z;
	b.w = 0;
	return (b);
}

t_vector	vector_crossproduct(t_vector a, t_vector b)
{
	t_vector c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	c.w = 0;
	return (c);
}
