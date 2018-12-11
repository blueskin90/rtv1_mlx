/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:02:17 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:02:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			cone_intersection(t_ray ray, t_obj *cone)
{
	float		a;
	float		b;
	float		c;
	float		d;

	float		l[2];
	t_vec		v1;
	t_vec		v2;
	float		tansquare;

	ray.pos = ray_to_obj(ray, cone).pos;
	ray.dir = ray_to_obj(ray, cone).dir;
	tansquare = tanf(cone->params.cone.angle);
	tansquare *= tansquare;
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y - ray.dir.z * ray.dir.z * tansquare;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y - 2 * ray.pos.z * ray.dir.z * tansquare;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - ray.pos.z * ray.pos.z * tansquare;
	d = b * b - 4 * a * c;
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
