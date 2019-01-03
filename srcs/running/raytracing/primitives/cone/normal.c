/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 02:44:37 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 15:47:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


// verifier que cette fonction soit biennnn !
void				get_conenormal(t_ray *ray)
{
	t_vec	center_to_hit;
	t_vec	axis1;
	t_vec	axis2;
	t_vec	hit_to_axis1;
	t_vec	hit_to_axis2;
	t_vec	real_axis;
	t_vec	rot_axis;
	t_vec	hypotenuse;
	float	hypotenuse_len;
	t_vec	normal;

	center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos); // a
	axis1 = vec_add(ray->obj_hit->dir, ray->obj_hit->pos);	
	axis2 = vec_add(vec_opposite(ray->obj_hit->dir), ray->obj_hit->pos);
	hit_to_axis1 = vec_init(ray->hit_pos, axis1);
	hit_to_axis2 = vec_init(ray->hit_pos, axis2);
	if (vec_magnitude(hit_to_axis1) < vec_magnitude(hit_to_axis2))
		real_axis = axis1;
	else
		real_axis = axis2;
	real_axis = vec_normalize(vec_sub(real_axis, ray->obj_hit->pos));
	rot_axis = vec_normalize(vec_opposite(vec_crossproduct(vec_normalize(center_to_hit), real_axis)));
	hypotenuse = vec_normalize(matrix_mult_vec(rotmatrix_axis_angle(rot_axis, degtorad(90)), real_axis));
	hypotenuse_len = vec_magnitude(center_to_hit) / cosf(degtorad(90) - ray->obj_hit->params.cone.angle);
	hypotenuse = vec_add(vec_mul(hypotenuse, hypotenuse_len), ray->obj_hit->pos);
	normal = vec_init(ray->hit_pos, hypotenuse);
	normal = vec_normalize(normal);
	ray->normal = normal;
	// marche pas, faire les derivees partielles de fonctions :D

}
