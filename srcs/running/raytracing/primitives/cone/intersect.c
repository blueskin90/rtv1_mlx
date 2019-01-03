/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:43:47 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 15:39:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		cone_get_variables(t_ray ray, t_obj *cone, float var[3])
{
	float		tansquare;

	tansquare = tanf(cone->params.cone.angle);
	tansquare *= tansquare;
	var[0] = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y - ray.dir.z
		* ray.dir.z * tansquare;
	var[1] = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y - 2
		* ray.pos.z * ray.dir.z * tansquare;
	var[2] = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - ray.pos.z
		* ray.pos.z * tansquare;
}

static float	cone_return_length(t_ray ray, float l[2])
{
	t_vec		v1;
	t_vec		v2;

	v1 = vec_mul(ray.dir, l[0]);
	v2 = vec_mul(ray.dir, l[1]);
	if (l[0] <= 0)
	{
		if (l[1] <= 0)
			return (INFINITY);
		return (vec_magnitude(v2));
	}
	if (l[1] <= 0)
		return (vec_magnitude(v1));
	if (l[0] < l[1])
		return (vec_magnitude(v1));
	return (vec_magnitude(v2));
}

float			cone_intersect(t_ray ray, t_obj *cone)
{
	float		var[3];
	float		l[2];

	ray = ray_to_obj(ray, cone);
	cone_get_variables(ray, cone, var);
	if (!quadratic(var[0], var[1], var[2], l))
		return (INFINITY);
	return (cone_return_length(ray, l));
}

static float	try_intersection(t_ray ray, t_obj *cone)
{
	return (cone_intersect(ray, cone));
}

void			cone_intersection(t_ray *ray, t_obj *cone)
{
	float		length;

	length = try_intersection(*ray, cone);
	check_for_closest(length, ray, cone);
}
