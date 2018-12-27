/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 03:11:04 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 04:34:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			running(t_args *args, t_scene *scenes)
{
	t_scene		*scene;
	t_obj		*camera;

	if (args->renderer_mode != NO_RENDERER)
	{
		scene = scenes;
		while (scene)
		{
			camera = scene->cameras;
			while (camera)
			{
				raytracing(scene, camera);
				camera = camera->next;
			}
			scene = scene->next;
		}
	}
	if (args->verbose_mode == RUNNING || args->verbose_mode == ALL_VERBOSE)
		verbose_running(args, scenes);
}
