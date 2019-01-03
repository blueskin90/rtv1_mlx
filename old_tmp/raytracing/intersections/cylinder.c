/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:01:29 by toliver           #+#    #+#             */
/*   Updated: 2018/12/16 17:57:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	float		a;
	float		b;
	float		c;

	float		l[2];
	t_vec		v1;
	t_vec		v2;

	ray = ray_to_obj(ray, cylinder);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	if (!quadratic(a, b, c, l))
		return (INFINITY);
	v1 = vec_mul(ray.dir, l[0]);
	v2 = vec_mul(ray.dir, l[1]);
	if (l[0] <= TOLERANCE)
	{
		if (l[1] <= TOLERANCE)
			return (INFINITY);
		return (vec_magnitude(v2) - TOLERANCE);
	}
	if (l[1] <= TOLERANCE)
		return (vec_magnitude(v1) - TOLERANCE);
	if (l[0] < l[1])
		return (vec_magnitude(v1) - TOLERANCE);
	return (vec_magnitude(v2) - TOLERANCE);
}
