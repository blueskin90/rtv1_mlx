/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:47:53 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 02:48:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				get_planenormal(t_ray *ray)
{
	t_vec	vec1;
	t_vec	vec2;

	vec1 = vec_add(ray->obj_hit->pos, ray->obj_hit->dir);
	vec2 = vec_add(ray->obj_hit->pos, vec_opposite(ray->obj_hit->dir));
	if (vec_magnitude(vec_init(ray->pos, vec1)) < vec_magnitude(vec_init(ray->pos, vec2)))
		ray->normal = ray->obj_hit->dir; // prendre celle qui fait le plus face au viewer
	else
		ray->normal = vec_opposite(ray->obj_hit->dir);
}
