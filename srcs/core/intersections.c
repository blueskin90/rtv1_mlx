/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/12/07 19:18:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** GO RANGER CE FICHIER, FEIGNASSE DE THOMAS
*/

#include "rtv1.h"

float			sphere_radius(t_obj *sphere)
{
	return (sphere->params.sphere.radius);
}

float			sphere_intersection(t_ray ray, t_obj *sphere)
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
			return (length - TOLERANCE);
		if (proj_to_center > sphere_radius(sphere))
			return (INFINITY);
		return (length - (sqrtf(powf(sphere_radius(sphere), 2) - powf(proj_to_center, 2))) - TOLERANCE);
	}
	return (INFINITY);
}

float			plane_intersection(t_ray ray, t_obj *plane)
{
	float		denom;
	float		length;
	t_vec		diff;

	diff = vec_sub(ray.pos, plane->pos);
//	diff = ray.pos;
	denom = vec_dotproduct(ray.dir, plane->dir);
	if (denom != 0)
	{
		length = -vec_dotproduct(diff, plane->dir) / denom;
		if (length > TOLERANCE)
			return (length - TOLERANCE);
	}
	return (INFINITY);
}

int				quadratic(float a, float b, float c, float l[2])
{
	float		d;

	if (a == 0.0)
		return (0);
	d = b * b - 4 * a * c;
	if (d < 0.0)
		return (0);
	d = sqrtf(d);
	l[0] = (-b + d) / (2 * a);
	l[1] = (-b - d) / (2 * a);
	return (2);
}

float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	float		a;
	float		b;
	float		c;
	float		d;

	float		l[2];
	t_vec		v1;
	t_vec		v2;

	ray = ray_to_obj(ray, cylinder);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	if (!quadratic(a, b, c, l))
		return (INFINITY);
//	d = b * b - 4 * a * c;
//	if (a == 0.0 || d <= 0)
//		return (INFINITY);
//	len1 = (-b + sqrtf(d)) / (2 * a);
//	len2 = (-b - sqrtf(d)) / (2 * a);
	v1 = vec_mul(ray.dir, l[0]);
	v2 = vec_mul(ray.dir, l[1]);
	if (l[0] <= TOLERANCE)
	{
		if (l[1] <= TOLERANCE)
			return (INFINITY);
//		return (l[1]);
		vec_magnitude(v2);
	}
	if (l[1] <= TOLERANCE)
//		return (l[0]);
		vec_magnitude(v1);
	if (l[0] < l[1])
		return (vec_magnitude(v1));
	//	return (l[0]);
	return (vec_magnitude(v2));
//	return (l[1]);
//		return (vec_magnitude(v1) - TOLERANCE);
//	return (vec_magnitude(v2) - TOLERANCE);
}
float			cone_intersection(t_ray ray, t_obj *cone)
{
	float		a;
	float		b;
	float		c;
	float		d;

	float		len1;
	float		len2;
	t_vec		v1;
	t_vec		v2;
	float		tansquare;
	

//	ray.pos = ray_to_obj(ray, cone).pos;
//	ray.dir = ray_to_obj(ray, cone).dir;
	tansquare = tanf(cone->params.cone.angle);
	tansquare *= tansquare;
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y- ray.dir.z * ray.dir.z * tansquare;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y - 2 * ray.pos.z * ray.dir.z * tansquare;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - ray.pos.z * ray.pos.z * tansquare;
	d = b * b - 4 * a * c;
	if (a == 0.0 || d <= 0)
		return (INFINITY);
	len1 = (-b + sqrtf(d)) / (2 * a);
	len2 = (-b - sqrtf(d)) / (2 * a);
	v1 = vec_mul(ray.dir, len1);
	v2 = vec_mul(ray.dir, len2);
	if (len1 <= 0 && len2 <= 0)
			return (INFINITY);
	if (len1 < len2)
		return (vec_magnitude(v1) - TOLERANCE);
	return (vec_magnitude(v2) - TOLERANCE);
}
