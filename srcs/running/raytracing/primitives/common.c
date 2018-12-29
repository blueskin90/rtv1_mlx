/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:49:39 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 10:15:00 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				quadratic(float a, float b, float c, float l[2])
{
	float		d;

	if (a == 0.0)
		return (0);
	d = b * b - 4 * a * c;
	if (d < TOLERANCE)
		return (0);
	d = sqrtf(d);
	l[0] = (-b + d) / (2 * a);
	l[1] = (-b - d) / (2 * a);
	return (2);
}

void				check_for_closest(float length, t_ray *ray, t_obj *obj)
{
	if (length < INFINITY && length < ray->length)
	{
		ray->obj_hit = obj;
		ray->length = length;
	}
}

void				get_normal(t_ray *ray)
{
	if (ray->obj_hit->type == SPHERE)
		get_spherenormal(ray);
	else if (ray->obj_hit->type == PLANE)
		get_planenormal(ray);
	else if (ray->obj_hit->type == CYLINDER)
		get_cylindernormal(ray);
	else if (ray->obj_hit->type == CONE)
		get_conenormal(ray);
	else
		ray->normal = vec_normalize(ray->obj_hit->dir);
}
