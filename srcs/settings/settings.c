/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 06:58:59 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			rederers_settings(t_args *args, t_env *env)
{
	t_obj		*scenes;
	t_obj		*cameras;

	scenes = env->scene;
	while (scenes)
	{
		cameras = scenes->cameras;
		while (cameras)
		{
			cameras = cameras->next;
		}
		scenes = scenes->next;
	}
}

void			settings(t_args *args, t_env *env)
{
//	step_set(SETTINGS);
	if (args->renderer_mode != NO_RENDERER)
		renderers_settings(args, env);
	if (args->verbose_mode == SETTINGS || args->verbose_mode == ALL_VERBOSE)
		verbose_settings(env);
}
