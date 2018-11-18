/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:25:54 by toliver           #+#    #+#             */
/*   Updated: 2018/11/18 17:25:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec_magnitude(t_vec a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

t_vec		vec_norm(t_vec a) 
{
	float		magnitude;
	t_vec	b;

	magnitude = vec_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vec	vec_normalize(t_vec a)
{
	float		magnitude;
	t_vec	b;

	magnitude = vec_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vec	vec_add(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = 0;
	return (c);
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0;
	return (c);
}

t_vec	vec_mul(t_vec a, float s)
{
	t_vec	b;

	b.x = a.x * s;
	b.y = a.y * s;
	b.z = a.z * s;
	b.w = 0;
	return (b);
}
