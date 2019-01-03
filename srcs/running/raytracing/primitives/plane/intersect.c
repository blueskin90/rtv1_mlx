/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:47:31 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 15:17:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			plane_intersect(t_ray ray, t_obj *plane)
{
	float		denom;
	float		length;
	t_vec		diff;

	diff = vec_sub(ray.pos, plane->pos);
	denom = vec_dotproduct(ray.dir, plane->dir);
	if (denom != 0)
	{
		length = -vec_dotproduct(diff, plane->dir) / denom;
		if (length > 0)
			return (length);
	}
	return (INFINITY);
}

static float	try_intersection(t_ray ray, t_obj *plane)
{
	return (plane_intersect(ray, plane));
}

void			plane_intersection(t_ray *ray, t_obj *plane)
{
	float		length;

	length = try_intersection(*ray, plane);
	check_for_closest(length, ray, plane);
}
