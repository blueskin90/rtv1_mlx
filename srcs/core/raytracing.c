/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 04:27:57 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 06:05:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				get_normal(t_ray *ray)
{
	if (ray->obj_hit->type == SPHERE)
		ray->normal = vec_norm(vec_init(ray->obj_hit->pos, ray->hit_pos));
	else if (ray->obj_hit->type == PLANE)
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
	else if (ray->obj_hit->type == CYLINDER)
	{
		// valeur absolue dotproduct to_hit . cylinderaxis
		t_vec	center_to_hit;
		float	len;
		t_vec	center_under_hit;
		center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos);
		len = vec_dotproduct(center_to_hit, ray->obj_hit->dir);
		center_under_hit = vec_add(ray->obj_hit->pos, vec_mul(ray->obj_hit->dir, len));
		ray->normal = vec_normalize(vec_init(center_under_hit, ray->hit_pos));
	}
	else if (ray->obj_hit->type == CONE)
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
	else
		ray->normal = ray->obj_hit->dir;
}



void				shoot_ray(t_ray *ray)
{
	t_obj			*objptr;
	float			current_hit;

	current_hit = INFINITY;
	objptr = scene_get()->objs;
	while (objptr)
	{
		if ((current_hit = objptr->intersect(*ray, objptr)) != INFINITY
			&& current_hit < ray->length)
		{
			ray->obj_hit = objptr;
			ray->length = current_hit;
		}
		objptr = objptr->next;
	}
	if (ray->length != INFINITY)
	{
		ray->hit_pos = vec_add(ray->pos, vec_mul(ray->dir, ray->length));
		get_normal(ray);
		ray->color = ray->obj_hit->color;
	}
	else
		ray->color = color_init_hsl(0x000000); 
}

void				raytracing(void)
{
	int				i;

	i = 0;
	while (i < renderer_getraymax())
	{
		shoot_ray(renderer_getray(i)); 
		i++;
	}
}

void				raytracing_lights(void)
{
	int				i;
	t_ray			*ray;

	i = 0;
	while (i < renderer_getraymax())
	{
		ray = renderer_getray(i);
		ray->color.rgb.value = colorization(ray, env_get());
		i++;
	}
}
