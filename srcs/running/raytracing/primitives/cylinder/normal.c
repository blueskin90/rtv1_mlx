/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:47:07 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 02:47:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				get_cylindernormal(t_ray *ray)
{
	t_vec	center_to_hit;
	float	len;
	t_vec	center_under_hit;

	center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos);
	len = vec_dotproduct(center_to_hit, ray->obj_hit->dir);
	center_under_hit = vec_add(ray->obj_hit->pos, vec_mul(ray->obj_hit->dir, len));
	ray->normal = vec_normalize(vec_init(center_under_hit, ray->hit_pos));
}
