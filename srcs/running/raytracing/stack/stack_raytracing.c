/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_raytracing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 03:45:08 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 23:32:49 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			stack_raytracing(t_scene *scene, t_renderer *renderer,
		t_obj *cam)
{
	int				x;
	int				y;
	t_ray			ray;

	y = 0;
	while (y < renderer->height)
	{
		x = 0;
		while (x < renderer->width)
		{
			ray = get_actual_ray(renderer, cam, x, y);
			shoot_ray(scene, &ray);
			if (renderer->print_mode > 2 && ray.length != INFINITY)
				shoot_ray_lights(scene, &ray, cam);
			if (renderer->print_mode > 0)
				mlx_px_to_img(renderer->img, x, y, ray.color.value);
			x++;
		}
		y++;
	}
	return ;
}
