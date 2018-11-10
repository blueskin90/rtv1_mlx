/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:25:54 by toliver           #+#    #+#             */
/*   Updated: 2018/11/10 20:14:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vector_magnitude(t_vector a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}
t_vector	vec_norm(t_vector a) 
{
	float		magnitude;
	t_vector	b;

	magnitude = vector_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vector	vector_normalize(t_vector a)
{
	float		magnitude;
	t_vector	b;

	magnitude = vector_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = 0;
	return (c);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0;
	return (c);
}

t_vector	vector_mul(t_vector a, float s)
{
	t_vector	b;

	b.x = a.x * s;
	b.y = a.y * s;
	b.z = a.z * s;
	b.w = 0;
	return (b);
}
