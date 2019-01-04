/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:16 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 01:13:00 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			renderers_settings(t_args *args, t_env *env)
{
	t_scene		*scenes;
	t_obj		*cameras;

	scenes = env->scene;
	while (scenes)
	{
		cameras = scenes->cameras;
		while (cameras)
		{
			cameras->params.camera.renderer = renderer_init(cameras, args, env);
			cameras = cameras->next;
		}
		scenes = scenes->next;
	}
}

void			settings(t_args *args, t_env *env)
{
	renderers_settings(args, env);
	if (args->verbose_mode == SETTINGS || args->verbose_mode == ALL_VERBOSE)
		verbose_settings(args, env);
}
