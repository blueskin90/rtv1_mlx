/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:16 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 19:48:06 by toliver          ###   ########.fr       */
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

void			tmp_colors_settings(t_scene *scene)
{
	t_scene		*scenes;
	t_obj		*obj;

	scenes = scene;
	while (scenes)
	{
		obj = scenes->objs;
		while (obj)
		{
			// tmp brillance setting
			obj->brillance = 100;
			obj->color = rgb_div(obj->color, 255.0);
			obj->specular = rgb_div(obj->specular, 255.0);
			obj->diffuse = rgb_div(obj->diffuse, 255.0);
			obj = obj->next;
		}
		obj = scenes->lights;
		while (obj)
		{
			obj->color = rgb_div(obj->color, 255.0);
			obj = obj->next;
		}
		scenes = scenes->next;
	}
}

void			settings(t_args *args, t_env *env)
{
//	step_set(SETTINGS);
	renderers_settings(args, env);
	tmp_colors_settings(env->scene); // a supprimer apres
	if (args->verbose_mode == SETTINGS || args->verbose_mode == ALL_VERBOSE)
		verbose_settings(args, env);
}
