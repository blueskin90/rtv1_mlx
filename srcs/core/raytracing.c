/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 04:27:57 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 11:40:24 by toliver          ###   ########.fr       */
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
		ray->normal = vec_normalize(ray->obj_hit->dir);
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
		ray->color = rgb_init(0x000000); 
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

t_ray			reflect_ray(t_ray *ray)
{
	t_matrix	rotmatrix;
	t_vec		reflected;

	rotmatrix = rotmatrix_axis_angle(ray->normal, degtorad(180));
	reflected = matrix_mult_vec(rotmatrix, vec_opposite(ray->dir));
	return (ray_init(ray->hit_pos, vec_norm(reflected)));
}
/*
t_vec			reflect_vector(t_vec vec, t_vec axis)
{
	return (vec_normalize(vec_mul(vec_sub(axis, vec),2 * vec_dotproduct(vec, axis))));
}
*/
t_vec			reflect_vector(t_vec vec, t_vec axis)
{
	t_matrix	rotmatrix;

	rotmatrix = rotmatrix_axis_angle(axis, degtorad(180));
	return (vec_normalize(matrix_mult_vec(rotmatrix, vec)));
}

t_RGB			get_specular(t_ray *ray, t_ray to_light, t_obj light)
{
	t_RGB		rgb;
	t_vec		reflect;
	t_vec		to_view;
	float		mult_value;
	float		dotproduct;

	dotproduct = vec_dotproduct(vec_normalize(vec_init(ray->hit_pos, light.pos)), ray->normal);
	if (dotproduct <= 0)
		return (rgb_init(0));
	reflect = reflect_vector(vec_normalize(vec_init(ray->hit_pos, light.pos)), ray->normal);
	to_view = vec_normalize(vec_init(ray->hit_pos, camera_get()->pos));
	mult_value = maxf(0, vec_dotproduct(reflect, to_view));
	mult_value = powf(mult_value, 100); // remplacer 100 par la value de shininess de l;objet
	mult_value *= light.params.light.intensity;
	rgb = rgb_mul(light.color, mult_value);
	rgb = rgb_mul_rgb(rgb, ray->obj_hit->color);
	(void)to_light;
	return (rgb);
}

t_RGB			get_diffuse(t_ray *ray, t_ray to_light, t_obj light)
{
	t_RGB		rgb;
	float		dotproduct;

	dotproduct = vec_dotproduct(ray->normal, vec_normalize(vec_init(ray->hit_pos, light.pos)));
	if (dotproduct <= 0)
		return (rgb_init(0));
	dotproduct *= light.params.light.intensity;
	rgb = rgb_mul(light.color, dotproduct);
	rgb = rgb_mul_rgb(rgb, ray->obj_hit->color);
	(void)to_light;
	return (rgb);
} // si ca donne mal, tenter le fabs du dotproduct

t_RGB			get_ambiant(t_ray *ray)
{
	(void)ray;
	return (rgb_mul_rgb(ray->obj_hit->color, rgb_mul(rgb_init(0xffffff), 0.2))); // maybe take into account some variable of the obj_hit and a varient ambiant_light;
}

void			shoot_ray_lights(t_ray *ray)
{
	t_RGB		finalcolor;
	t_obj		*ptr;
	t_ray		to_light;

	if (ray->length == INFINITY)
		return;
	finalcolor = get_ambiant(ray); // pas sur que ce soit logique de ne pas prendre en compte les lumieres actuelles
	ptr = scene_get()->lights;
	while (ptr)
	{
		to_light = ray_init_lookat(ray->hit_pos, ptr->pos);
		shoot_ray(&to_light);
		if (to_light.length > vec_magnitude(vec_init(ray->hit_pos, ptr->pos)))
		{ 
			// si on fait pas le cheat de mort, supprimer la tolerance
			finalcolor = rgb_add(finalcolor, get_diffuse(ray, to_light, *ptr));
			finalcolor = rgb_add(finalcolor, get_specular(ray, to_light, *ptr));
		}
		ptr = ptr->next;
	}
	ray->color = finalcolor;
}

void				raytracing_lights(void)
{
	int				i;

	i = 0;
	while (i < renderer_getraymax())
	{
		shoot_ray_lights(renderer_getray(i));
		i++;
	}
}
