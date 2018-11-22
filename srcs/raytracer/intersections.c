/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/11/22 04:09:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				is_equal_float(float a, float b)
{
	float		c;

	c = a - b;
	c = (c < 0) ? -c : c;
	if (c < 0.00001)
		return (1);
	return (0);
}

int				is_equal_vec(t_vec a, t_vec b)
{
	if (is_equal_float(a.x, b.x) && is_equal_float(a.y, b.y)
		&& is_equal_float(a.z, b.z))
		return (1);
	return (0);
}

int				is_opposite_vec(t_vec a, t_vec b)
{
	return (is_equal_vec(a, vec_opposite(b)));
}

float			sphere_radius(t_obj *sphere)
{
	return (sphere->params.sphere.radius);
}

float			sphere_intersection(t_ray ray, t_obj *sphere)
{
	t_vec		origin_to_sphere;
	float		length;
	float		proj_to_center;

	origin_to_sphere = vec_init(ray.origin, sphere->pos);
	length = vec_dotproduct(ray.direction, origin_to_sphere); // projette le centre de la sphere sur le vecteur de rayon et retourne la longueur
	if (is_equal_float(length, 0.0) || length < 0) // attention si la sphere est derriere et assey grande pour etre vue de l'interieur ?
		return (INFINITY);
	else
	{
		proj_to_center = powf(vec_magnitude(origin_to_sphere), 2) - powf(length, 2);
		proj_to_center = (proj_to_center < 0) ? sqrtf(-proj_to_center) : sqrtf(proj_to_center);
		if (is_equal_float(proj_to_center, sphere_radius(sphere)))
			return (length);
		if (proj_to_center > sphere_radius(sphere) + 0.000001)
			return (INFINITY);
		return (length - (sqrtf(powf(sphere_radius(sphere), 2) - powf(proj_to_center, 2))));
	}
	return (INFINITY);
}

float			plane_intersection(t_ray ray, t_obj *plane)
{
	float		denom;
	float		length;
	t_vec		diff;

	diff = vec_sub(ray.origin, plane->pos);
	denom = vec_dotproduct(ray.direction, plane->params.plane.normal);
	if (!isequalfloat(denom, 0.0))
	{
		length = -vec_dotproduct(diff, plane->params.plane.normal) / denom;
		if (length > TOLERANCE)
			return (length);
	}
/*	denom = vec_dotproduct(ray.direction, plane->params.plane.normal);
	if (!isequalfloat(denom, 0.0))
	{
		length = vec_dotproduct(vec_init(ray.origin, plane->pos), ray.direction) / fabs(denom);
		if (length > TOLERANCE)
			return (length);
		return (INFINITY);
	}
	*/
	return (INFINITY);
}

/*
float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	t_vec		to_center;
	float		a;
	float		b;
	float		c;
	float		delta;
	float		length;

	to_center = vec_init(ray.origin, cylinder->pos);
	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	b = ray.direction.x * to_center.x + ray.direction.z * to_center.z;
	c = to_center.x * to_center.x + to_center.z * to_center.z - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	delta = b * b - a * c;
	if (delta < TOLERANCE)
		return (INFINITY);
	length = (-b - sqrtf(delta)) / a;
	if (length < TOLERANCE)
		return (INFINITY);
	return (length);
}
*/

float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	float		a;
	float		b;
	float		c;
	float		delta;
	float		length;

	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	b = (2 * (ray.direction.x * (ray.origin.x - cylinder->pos.x))) + (2 * (ray.direction.z * (ray.origin.z - cylinder->pos.z)));
	c = powf(ray.origin.x - cylinder->pos.x, 2) + powf(ray.origin.z - cylinder->pos.z, 2) - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	delta = b * b - 4 * a * c;
	if (delta < TOLERANCE)
		return (INFINITY);
	length = ((-b - sqrtf(delta)) / (2 * a)) > TOLERANCE ? (-b - sqrtf(delta)) / (2 * a) : (-b + sqrtf(delta)) / (2 * a);
	return (length - TOLERANCE);
}
