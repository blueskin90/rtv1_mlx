/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 17:06:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		colorization(t_env *env, t_ray ray, double nearest, t_obj *sphere)
{
	t_vector	ray_hit;
	t_vector	norm_hit;
	t_vector	light_ray;
	float		c;
	t_vector	temp;
	t_obj		*objs_hit;
	t_hsl		hsl;
	

//	printf("COLORIZATION\n");
	ray_hit = vector_mul(ray.direction, nearest);
	norm_hit = vector_sub(ray_hit, vector_init(vertex_init(0,0,0),sphere->pos));
	norm_hit = vec_norm(norm_hit);
	c = vec_dot(norm_hit, ray.direction);
	// ? 
	if (c <= 0)
	{	
		//printf("INSIDE\n");
		return (0);
	}
	// une seule light
	light_ray = vector_sub(vector_init(vertex_init(0,0,0), env->scene->light->pos), ray_hit);
	light_ray = vec_norm(light_ray);
	temp = vector_add(ray_hit, norm_hit);
	// DONT FORGET TO THINK ABOUT OBJECT THAT ARE AFTER THE LIGHT
	if ((c = shoot_ray(ray_init(vertex_init(temp.x, temp.y, temp.z), light_ray),
				env, &objs_hit)) != INFINITY)
	{
		return (0);
	}
	double val;
	val = vec_dot(norm_hit, light_ray);
	//float angle = acosf(val);
	//printf("angle : %f\n", radtodeg(angle));
	if (val >= 0){
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = val;
		return hsl_to_rgb(hsl);
	/*	printf("rgb : [%d][%d][%d] hsv : [%d][%d][%d]\n", sphere->color.rgb.r, 
				sphere->color.rgb.g, 
				sphere->color.rgb.b, 
				sphere->color.type.hsl.h,
				sphere->color.type.hsl.s,
				sphere->color.type.hsl.l);*/

	/*	if (val >= 1){
			return 0x000000;
		}
		return (255.0 * val);*/
	}
	return 0x000000;
}
