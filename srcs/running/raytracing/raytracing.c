/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 03:44:10 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 04:36:43 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			raytracing(t_scene *scene, t_obj *camera)
{
	t_renderer	*renderer;

	renderer = camera->params.camera.renderer;
	if (renderer->renderer_mode == STACK)
		stack_raytracing(scene, renderer, camera);
	else if (renderer->renderer_mode == MALLOC)
		malloc_raytracing(scene, renderer, camera);
	else
		ft_printf("Not yet implemented !\n");
}
