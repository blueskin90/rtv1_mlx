/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 19:59:40 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/11 00:00:13 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

int		colorization(t_env *env, t_vector *ray, double nearest, t_sphere *sphere)
{
	t_vector	ray_hit;
	t_vector	norm_hit;
	t_vector	light_ray;
	float		c;
	t_vector	temp;
	t_sphere	*objs_hit;
	

	ray_hit = vector_mul(ray, nearest);
	norm_hit = vector_init(sphere->pos, ray_hit);
	norm_hit = vec_norm(norm_hit);
	c = -vec_dot(norm_hit, ray);
	if (c <= 0)
		return (0);
	// une seule light
	light_ray = vector_init(ray_hit, env->scene->light->pos);
	light_ray = vec_norm(light_ray);
	temp = vector_add(ray_hit, norm_hit);
	if (c = shoot_ray(ray_init(temp, light_ray), env, &objs_hit))
	{
		return (0);
	}

	double val;
	val = vec_norm(norm_hit, light_ray);
	if (val >= 0){
		if (val > 1){
			return 0x0000FF;
		}
		return (255.0 * val);
	}
	return 0x0000FF;
}
