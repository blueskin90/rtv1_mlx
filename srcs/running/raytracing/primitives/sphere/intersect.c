/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:48:10 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 10:16:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


float			sphere_radius(t_obj *sphere)
{
	return (sphere->params.sphere.radius);
}

float			sphere_intersect(t_ray ray, t_obj *sphere)
{
	t_vec		origin_to_sphere;
	float		length;
	float		proj_to_center;

	origin_to_sphere = vec_init(ray.pos, sphere->pos);
	length = vec_dotproduct(ray.dir, origin_to_sphere); // projette le centre de la sphere sur le vecteur de rayon et retourne la longueur
	if (length <= 0) // attention si la sphere est derriere et assey grande pour etre vue de l'interieur ?
		return (INFINITY);
	else
	{
		proj_to_center = powf(vec_magnitude(origin_to_sphere), 2) - powf(length, 2);
		proj_to_center = (proj_to_center < 0) ? sqrtf(-proj_to_center) : sqrtf(proj_to_center);
		if (is_equal_float(proj_to_center, sphere_radius(sphere)))
			return (length);
		if (proj_to_center > sphere_radius(sphere))
			return (INFINITY);
		return (length - (sqrtf(powf(sphere_radius(sphere), 2) - powf(proj_to_center, 2))));
	}
	return (INFINITY);
}

static float		try_intersection(t_ray ray, t_obj *sphere)
{
	return (sphere_intersect(ray, sphere));
}

void			sphere_intersection(t_ray *ray, t_obj *sphere)
{
	float		length;

	length = try_intersection(*ray, sphere);
	check_for_closest(length, ray, sphere);
}
