/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:48:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 03:40:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				get_spherenormal(t_ray *ray)
{
	ray->normal = vec_norm(vec_init(ray->obj_hit->pos, ray->hit_pos));
}
