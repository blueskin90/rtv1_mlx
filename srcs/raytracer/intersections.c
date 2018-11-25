/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/11/25 06:29:58 by toliver          ###   ########.fr       */
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
		if (proj_to_center > sphere_radius(sphere) + TOLERANCE)
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

	diff = vec_sub(ray.origin, plane->pos);
	denom = vec_dotproduct(ray.direction, plane->params.plane.normal);
	if (!isequalfloat(denom, 0.0))
	{
		length = -vec_dotproduct(diff, plane->params.plane.normal) / denom;
		if (length > TOLERANCE)
			return (length - TOLERANCE);
	}
	return (INFINITY);
}
/*
int				quadratic(float a, float b, float c, float s[2])
{
	float		d;
	if (a == 0.0)
		return (0);
	d = b * b - 4 * a * c;
	if (d < 0.0)
		return (-1);
	d = sqrt(d);
	s[0] = (-b + d) / (2 * a);
	s[1] = (-b - d) / (2 * a);
	return (2);
}
*/
t_ray			ray_to_cylinder(t_ray ray, t_obj *cyl)
{
	t_ray		new_ray;

	new_ray = ray_init(ray.origin, ray.direction);
	new_ray.origin = vec_sub(ray.origin, cyl->pos);
	if (cyl->world_to_obj_angle != NAN)
		new_ray.origin = matrix_mult_vec(cyl->world_to_obj, new_ray.origin);
	new_ray.direction = vec_add(ray.origin, ray.direction);
	new_ray.direction = vec_sub(new_ray.direction, cyl->pos);
	if (cyl->world_to_obj_angle != NAN)
		new_ray.direction = matrix_mult_vec(cyl->world_to_obj, new_ray.direction);
	new_ray.direction = vec_sub(new_ray.direction, new_ray.origin);
	new_ray.direction = vec_norm(new_ray.direction);
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

	ray = ray_to_cylinder(ray, cylinder);
	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.y * ray.direction.y;
	c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	d = b * b - 4 * a * c;
	if (a == 0.0 || d <= TOLERANCE)
		return (INFINITY);
	len1 = (-b + sqrtf(d)) / (2 * a);
	len2 = (-b - sqrtf(d)) / (2 * a);
	v1 = vec_mul(ray.direction, len1);
	v2 = vec_mul(ray.direction, len2);
	if (len1 < TOLERANCE && len2 < TOLERANCE)
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

	ray = ray_to_cylinder(ray, cone);
	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y- ray.direction.z * ray.direction.z;
	b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.y * ray.direction.y - 2 * ray.origin.z * ray.direction.z;
	c = ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y - ray.origin.z * ray.origin.z ;
	d = b * b - 4 * a * c;
	if (a == 0.0 || d <= TOLERANCE)
		return (INFINITY);
	len1 = (-b + sqrtf(d)) / (2 * a);
	len2 = (-b - sqrtf(d)) / (2 * a);
	v1 = vec_mul(ray.direction, len1);
	v2 = vec_mul(ray.direction, len2);
	if (len1 < TOLERANCE && len2 < TOLERANCE)
			return (INFINITY);
	len1 = vec_magnitude(v1);
	len2 = vec_magnitude(v2);
	if (len1 < len2)
		return (len1 - TOLERANCE);
	return (len2 - TOLERANCE);
	return (INFINITY);
}
