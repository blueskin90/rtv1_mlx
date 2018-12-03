/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 11:39:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** GO RANGER CE FICHIER, FEIGNASSE DE THOMAS
*/

#include "rtv1.h"

int				is_equal_float(float a, float b)
{
	float		c;

	c = a - b;
	c = (c < 0) ? -c : c;
	if (c < TOLERANCE)
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

t_ray			ray_init_lookat(t_vec pos, t_vec lookat)
{
	return (ray_init(pos, vec_sub(lookat, pos)));
}

t_ray			ray_init(t_vec pos, t_vec dir)
{
	t_ray		ray;

	ft_bzero(&ray, sizeof(t_ray));
	ray.length = INFINITY;
	ray.pos = pos;
	ray.dir = vec_norm(dir);
	return (ray);
}
t_ray			ray_to_obj(t_ray ray, t_obj *cyl)
{
	t_ray		new_ray;

	new_ray = ray_init(ray.pos, ray.dir);
	new_ray.pos = vec_sub(ray.pos, cyl->pos);
	new_ray.pos = matrix_mult_vec(cyl->obj_to_world, new_ray.pos);
	new_ray.dir = vec_add(ray.pos, ray.dir);
	new_ray.dir = vec_sub(new_ray.dir, cyl->pos);
	new_ray.dir = matrix_mult_vec(cyl->obj_to_world, new_ray.dir);
	new_ray.dir = vec_sub(new_ray.dir, new_ray.pos);
	new_ray.dir = vec_norm(new_ray.dir);
	return (new_ray);
}

float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	float		a;
	float		b;
	float		c;
	float		d;

	float		len1;
	float		len2;
	t_vec		v1;
	t_vec		v2;

	ray = ray_to_obj(ray, cylinder);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	d = b * b - 4 * a * c;
	if (a == 0.0 || d <= 0)
		return (INFINITY);
	len1 = (-b + sqrtf(d)) / (2 * a);
	len2 = (-b - sqrtf(d)) / (2 * a);
	v1 = vec_mul(ray.dir, len1);
	v2 = vec_mul(ray.dir, len2);
	if (len1 <= 0 && len2 <= 0)
			return (INFINITY);
	len1 = vec_magnitude(v1);
	len2 = vec_magnitude(v2);
	if (len1 < len2)
		return (len1 - TOLERANCE);
	return (len2 - TOLERANCE);
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

	ray = ray_to_obj(ray, cone);
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
	len1 = vec_magnitude(v1);
	len2 = vec_magnitude(v2);
	if (len1 < len2)
		return (len1 - TOLERANCE);
	return (len2 - TOLERANCE);
	return (INFINITY);
}
