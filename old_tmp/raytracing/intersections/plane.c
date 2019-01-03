/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:01:12 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:01:24 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
