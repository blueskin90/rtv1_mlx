/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 05:32:09 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		colorization(t_env *env, t_ray ray, float nearest, t_obj *obj_hit)
{
	t_vec		hit_pos;
	t_vec		normal;
	t_vec		to_light;
	t_hsl		color;
	float		ratio;
	float		to_light_hit;
	t_obj		*to_light_hit_obj;	

	hit_pos = vec_add(vec_mul(ray.direction, nearest), ray.origin);
	to_light = vec_norm(vec_init(hit_pos, env->scene->light->pos));
	to_light_hit = shoot_ray(ray_init(hit_pos, to_light), env, &to_light_hit_obj);
	color.h = obj_hit->color.type.hsl.h;
	color.s = obj_hit->color.type.hsl.s;
	color.l = obj_hit->color.type.hsl.l;
	if (to_light_hit != INFINITY && to_light_hit < vec_magnitude(vec_init(hit_pos, env->scene->light->pos)))
	{
		color.l *= 0.01;
		return (hsl_to_rgb(color));
	}
	if (obj_hit->type == SPHERE)
		normal = vec_norm(vec_init(obj_hit->pos, hit_pos));
	else if (obj_hit->type == PLANE)
	{
		normal = vec_norm(obj_hit->params.plane.normal);
	}
	else
		normal = obj_hit->rot;
	ratio = vec_dotproduct(normal, to_light);
	ratio = (ratio < 0.01 ) ? 0.01 : ratio;
	color.l *= ratio;
	return (hsl_to_rgb(color));
}	

/*
int		colorization(t_env *env, t_ray ray, float nearest, t_obj *sphere)
{
	t_vec	ray_hit;
	t_vec	norm_hit;
	t_vec	light_ray;
	float		c;
	t_vec	temp;
	t_obj		*objs_hit;
	t_hsl		hsl;
	

//	printf("COLORIZATION\n");
	ray_hit = vec_mul(ray.direction, nearest);
	norm_hit = vec_sub(ray_hit, sphere->pos);
	norm_hit = vec_norm(norm_hit);
//	c = vec_dot(norm_hit, ray.direction);
//	f (c < 0)
//	{	
//		//printf("INSIDE\n");
//		return (0xffea00);
//	}
	// une seule light
	light_ray = vec_init(ray_hit, env->scene->light->pos);
	light_ray = vec_norm(light_ray);
	temp = vec_add(ray_hit, norm_hit);
	// DONT FORGET TO THINK ABOUT OBJECT THAT ARE AFTER THE LIGHT
	if ((c = shoot_ray(ray_init(ray_hit, light_ray),
				env, &objs_hit)) != INFINITY && c < vec_magnitude(vec_init(ray_hit, env->scene->light->pos)))
	{
//		printf("ray_hit : ");
//		print_vec(ray_hit);
//		printf("point : %f,%f,%f\n",temp.x, temp.y, temp.z);
//		printf("%#x\n", objs_hit->color.rgb.value);
//		printf("center of object : ");
//		print_vec(objs_hit->pos);
//		
		return (0x123456);
	}
	float val;
	val = vec_dot(norm_hit, light_ray);
	if (val > g_biggest)
		g_biggest = val;
	if (val < g_smallest)
		g_smallest = val;
	//printf("val : %f\n", val);
	//float angle = acosf(val);
	//printf("angle : %f\n", radtodeg(angle));
	if (fabs(val) >= TOLERANCE){
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = val * 0.5 + 0.5;
		if (hsl.l > 1)
			hsl.l = 1;
		return hsl_to_rgb(hsl);
	//	printf("rgb : [%d][%d][%d] hsv : [%d][%d][%d]\n", sphere->color.rgb.r, 
	//			sphere->color.rgb.g, 
	//			sphere->color.rgb.b, 
	//			sphere->color.type.hsl.h,
	//			sphere->color.type.hsl.s,
	//			sphere->color.type.hsl.l);

//		if (val >= 1){
//			return 0x000000;
//		}
//		return (255.0 * val);
	}
	else {
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = 0.1;
		//return hsl_to_rgb(hsl);
	}
	return 0x000000;
}*/
