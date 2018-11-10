/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 23:27:56 by toliver           #+#    #+#             */
/*   Updated: 2018/11/10 19:51:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float			sphere_intersection(t_sphere *sphere, t_vector ray)
{
	t_vector	origin_to_sphere;
	float		length;
	float		proj_to_center;
	float		origin_to_sphere_m;

	origin_to_sphere = vector_init(vertex_init(0,0,0), sphere->pos);
	length = vector_dotproduct(ray, origin_to_sphere); // projette le centre de la sphere sur le vecteur de rayon et retourne la longueur
	if (length <= 0) // attention si la sphere est derriere et assey grande pour etre vue de l'interieur ?
		return (INFINITY);
	else
	{
		proj_to_center = sqrtf(powf(vector_magnitude(origin_to_sphere), 2) 
				- powf(length, 2));
		if (proj_to_center > sphere->radius)
			return (INFINITY);
		if (proj_to_center == sphere->radius)
			return (length);
		if (proj_to_center < sphere->radius)
		{
			return (length - (sqrtf(powf(sphere->radius, 2) - powf(proj_to_center, 2))));
		}
	}
	return (INFINITY);
}
