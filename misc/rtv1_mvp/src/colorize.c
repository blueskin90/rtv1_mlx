/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:05:43 by cvermand          #+#    #+#             */
/*   Updated: 2018/06/25 13:19:52 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

unsigned int	colorization(t_env env, t_v3 *ray, double near, int obj_index)
{
	t_v3	ray_hit;
	t_v3	norm_hit;
	t_v3	light_ray;
	double	c;
	t_v3	temp;

	temp = ft_v3_scalar(ray, near);
	ray_hit = ft_v3_add(&env.cam->pt, &temp);
	//printf("x : %f y: %f z : %f\n", ray_hit.x, ray_hit.y, ray_hit.z);
	norm_hit = ft_v3_sustract(&ray_hit, &env.objs[obj_index]->pt);
	ft_v3norm(&norm_hit);
	c = -ft_v3_dot(&norm_hit, ray);
	if (c <= 0) 
	{
		ft_printf("inside c : %f\n", c);
		return (0);
	}
	light_ray = ft_v3_sustract(&env.light, &ray_hit);
	ft_v3norm(&light_ray);
	//printf("L x : %f y: %f z : %f\n", light_ray.x, light_ray.y, light_ray.z);
	/*temp = ft_v3_scalar(&norm_hit, 1e-4);
	temp = ft_v3_add(&ray_hit, &temp);*/
	temp = ft_v3_add(&ray_hit, &norm_hit);
	if ((c = intersection_distance(env, &light_ray, &temp, &obj_index)) != INFINITY)
	{
	//	printf("c : %f\n", c);
		return (0);
	}
//	ray_hit =
	//printf("max : %f other : %f\n", fmax(0.0, ft_v3_dot(&norm_hit, &light_ray)), ft_v3_dot(&norm_hit, &light_ray));
	double val;
	val =  ft_v3_dot(&norm_hit, &light_ray);
	if (val >= 0)
	{	
//		if (val > env.high_light)
//			env.high_light = val;
//		if (val < env.low_light)
//			env.low_light = val;
//		env.nbr_light = env.nbr_light + 1;
//		env.total_light = env.total_light + val;
//		ft_printf("%f\n", val);
		if (val > 1){
			printf("AAAAA\n");
			return 0x0000FF;
		}
		return (255.0 * val);
	}
	return (0.0);
}
