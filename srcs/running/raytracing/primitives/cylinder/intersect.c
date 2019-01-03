/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:46:09 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 15:40:18 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		cylinder_get_variables(t_ray ray, t_obj *cylinder, float var[3])
{
	var[0] = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	var[1] = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y;
	var[2] = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y
		- cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
}

static float	cylinder_return_length(t_ray ray, float l[2])
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
	if (l[1] <= TOLERANCE)
		return (vec_magnitude(v1));
	if (l[0] < l[1])
		return (vec_magnitude(v1));
	return (vec_magnitude(v2));
}

float			cylinder_intersect(t_ray ray, t_obj *cylinder)
{
	float		var[3];
	float		l[2];

	ray = ray_to_obj(ray, cylinder);
	cylinder_get_variables(ray, cylinder, var);
	if (!quadratic(var[0], var[1], var[2], l))
		return (INFINITY);
	return (cylinder_return_length(ray, l));
}

static float	try_intersection(t_ray ray, t_obj *cylinder)
{
	return (cylinder_intersect(ray, cylinder));
}

void			cylinder_intersection(t_ray *ray, t_obj *cylinder)
{
	float		length;

	length = try_intersection(*ray, cylinder);
	check_for_closest(length, ray, cylinder);
}
