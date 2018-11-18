/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/11/18 15:12:02 by cvermand         ###   ########.fr       */
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

int				is_equal_vector(t_vector a, t_vector b)
{
	if (is_equal_float(a.x, b.x) && is_equal_float(a.y, b.y)
		&& is_equal_float(a.z, b.z))
		return (1);
	return (0);
}

int				is_opposite_vector(t_vector a, t_vector b)
{
	return (is_equal_vector(a, vector_opposite(b)));
}

float			sphere_radius(t_obj *sphere)
{
	return (sphere->params.sphere.radius);
}

float			sphere_intersection(t_ray ray, t_obj *sphere)
{
	t_vector	origin_to_sphere;
	float		length;
	float		proj_to_center;

	origin_to_sphere = vector_init(ray.origin, sphere->pos);
	length = vector_dotproduct(ray.direction, origin_to_sphere); // projette le centre de la sphere sur le vecteur de rayon et retourne la longueur
	if (is_equal_float(length, 0.0) || length < 0) // attention si la sphere est derriere et assey grande pour etre vue de l'interieur ?
		return (INFINITY);
	else
	{
		proj_to_center = powf(vector_magnitude(origin_to_sphere), 2) - powf(length, 2);
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

	denom = vector_dotproduct(ray.direction, plane->params.plane.normal);
	if (!fabs(is_equal_float(denom, 0.0)))
	{
		length = vector_dotproduct(vector_init(ray.origin, plane->pos), ray.direction) / denom;
		if (length > 0.0)
			return (length);
		return (INFINITY);
	}
	return (INFINITY);
}
