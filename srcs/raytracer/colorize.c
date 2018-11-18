/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 23:39:06 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
	/*c = vec_dot(norm_hit, ray.direction);
	f (c < 0)
	{	
		//printf("INSIDE\n");
		return (0xffea00);
	}*/
	// une seule light
	light_ray = vec_sub(env->scene->light->pos, ray_hit);
	//print_vec(light_ray);
	light_ray = vec_norm(light_ray);
	//temp = vec_add(ray_hit, norm_hit);
	// DONT FORGET TO THINK ABOUT OBJECT THAT ARE AFTER THE LIGHT
	if ((c = shoot_ray(ray_init(ray_hit, light_ray), env, &objs_hit)) != INFINITY && c < vec_magnitude(vec_init(ray_hit, env->scene->light->pos)))
	{
		t_vec	test;
		test = vec_init(sphere->pos, ray_hit);
		printf("magnitude : %f\n", vec_magnitude(test));
		printf("distance hit : %f\n", c);
		printf("light ray : ");
		print_vec(light_ray);
		printf("ray_hit : ");
		print_vec(ray_hit);
		printf("point : %f,%f,%f\n",temp.x, temp.y, temp.z);
		printf("%#x\n", objs_hit->color.rgb.value);
		printf("center of object : ");
		print_vec(objs_hit->pos);
		printf("\n\n\n");
		return (0x123456);
		//return (0);
	}
	double val;
	val = vec_dot(norm_hit, light_ray);
	//printf("val : %f\n", val);
	//float angle = acosf(val);
	//printf("angle : %f\n", radtodeg(angle));
	hsl.l = val * 0.5 + 0.2;
	if (hsl.l >= 0){
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		//hsl.l = (val + 1)/2;
	//	hsl.l = val * 0.5 + 0.1;
		if (hsl.l > g_biggest)
			g_biggest = hsl.l;
		if (hsl.l < g_smallest)
			g_smallest = hsl.l;
		if (hsl.l > 1)
			hsl.l = 1;
		return hsl_to_rgb(hsl);
	}
	else {
		hsl.h = sphere->color.type.hsl.h;
		hsl.s = sphere->color.type.hsl.s;
		//hsl.l = sphere->color.type.hsl.l;
		hsl.l = 0.04;
//		return hsl_to_rgb(hsl);
		return (0);
	}
	return (0);
	//return 0x000000;
}
