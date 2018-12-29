/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_shooting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 03:26:38 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 08:51:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void				add_tolerance(t_ray *ray)
{
	ray->hit_pos = vec_add(ray->hit_pos, vec_mul(ray->normal, TOLERANCE)); // ca c'est pour la tolerance, ressortir un peu de l'objet, si ca merde, voir ici !
}

static void				set_ray_hitparams(t_ray *ray)
{
	if (ray->length == INFINITY)
	{
		ray->color = rgb_init(0x000000);
		return ;
	}
	ray->hit_pos = vec_add(ray->pos, vec_mul(ray->dir, ray->length));
	get_normal(ray);
	add_tolerance(ray);
	ray->color = ray->obj_hit->color;
}

void				shoot_ray(t_scene *scene, t_ray *ray)
{
	t_obj			*objptr;
	float			current_hit;

	current_hit = INFINITY;
	objptr = scene->objs;
	while (objptr)
	{
		objptr->intersect(ray, objptr);
		objptr = objptr->next;
	}
	set_ray_hitparams(ray);
}
