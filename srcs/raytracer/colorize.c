/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/11 00:26:21 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		colorization(t_env *env, t_ray ray, double nearest, t_sphere *sphere)
{
	t_vector	ray_hit;
	t_vector	norm_hit;
	t_vector	light_ray;
	float		c;
	t_vector	temp;
	t_sphere	*objs_hit;
	

//	printf("COLORIZATION\n");
	ray_hit = vector_mul(ray.dir, nearest);
	norm_hit = vector_sub(ray_hit, vector_init(vertex_init(0,0,0),sphere->pos));
	norm_hit = vec_norm(norm_hit);
	c = vec_dot(norm_hit, ray.dir);
	if (c <= 0)
	{
		//printf("dot c\n");
		//printf("dot c : %f\n", c);
		return (0);
	}
	// une seule light
	light_ray = vector_sub(vector_init(vertex_init(0,0,0), env->scene->light->pos), ray_hit);
	light_ray = vec_norm(light_ray);
	temp = vector_add(ray_hit, norm_hit);
	if ((c = shoot_ray(ray_init(vertex_init(temp.x, temp.y, temp.z), light_ray),
				env, &objs_hit)) != INFINITY)
	{
		printf("c nearest : %f\n", c);
		return (0);
	}
	double val;
		printf("NO HIT FOUND\n");
	val = vec_dot(norm_hit, light_ray);
	if (val >= 0){
		if (val > 1){
			printf("NOP \n");
			return 0x0000FF;
		}
		return (255.0 * val);
	}
	return 0x0000FF;
}
