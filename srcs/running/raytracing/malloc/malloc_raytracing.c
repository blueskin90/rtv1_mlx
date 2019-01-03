/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_raytracing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 03:45:34 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 10:58:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			malloc_raytracing(t_scene *scene, t_renderer *renderer,
		t_obj *cam)
{
	int				i;
	int				raymax;

	i = 0;
	raymax = renderer->height * renderer->width * renderer->depth;
	while (i < raymax)
	{
		shoot_ray(scene, &renderer->renderer[i]);
		i++;
	}
	i = 0;
	if (renderer->print_mode > 2)
	{
		while (i < raymax)
		{
			shoot_ray_lights(scene, &renderer->renderer[i], cam);
			i++;
		}
	}
}
