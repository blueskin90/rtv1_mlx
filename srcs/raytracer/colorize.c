/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 19:24:50 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		colorization(t_env *env, t_ray ray, float nearest, t_obj *sphere)
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
	/*c = vec_dot(norm_hit, ray.direction);
	f (c < 0)
	{	
		//printf("INSIDE\n");
		return (0xffea00);
	}*/
	// une seule light
	light_ray = vector_sub(vector_init(vertex_init(0,0,0), env->scene->light->pos), ray_hit);
	light_ray = vec_norm(light_ray);
	temp = vector_add(ray_hit, norm_hit);
	// DONT FORGET TO THINK ABOUT OBJECT THAT ARE AFTER THE LIGHT
	if ((c = shoot_ray(ray_init(vertex_init(temp.x, temp.y, temp.z), light_ray),
				env, &objs_hit)) != INFINITY && c < vector_magnitude(vector_init(vertex_init(ray_hit.x, ray_hit.y, ray_hit.z), env->scene->light->pos)))
	{
		printf("ray_hit : ");
		print_vector(ray_hit);
		printf("point : %f,%f,%f\n",temp.x, temp.y, temp.z);
		printf("%#x\n", objs_hit->color.rgb.value);
		printf("center of object : ");
		print_vertex(objs_hit->pos);
		return (0x123456);
	}
	double val;
	val = vec_dot(norm_hit, light_ray);
	if (val > g_biggest)
		g_biggest = val;
	if (val < g_smallest)
		g_smallest = val;
	//printf("val : %f\n", val);
	//float angle = acosf(val);
	//printf("angle : %f\n", radtodeg(angle));
	if (val >= -1){
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = val/1.5 * 0.5 + 0.33;
		if (hsl.l > 1)
			hsl.l = 1;
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
	else {
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = 0.1;
		//return hsl_to_rgb(hsl);
	}
	return 0x000000;
}
