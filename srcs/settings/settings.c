/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 06:28:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 21:59:36 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec			get_actual_dir(t_vec topleft, t_vec inc, int x, int y)
{
	t_vec		final;

	final = vec_init0(topleft.x + x * inc.x, topleft.y + y * inc.y, topleft.z);
	final = vec_normalize(final);
	return (final);
}

t_vec		get_top_left_vec(t_obj *cam, t_vec *increment, t_win *win)
{
	float		x;
	float		y;
	float		half_fovrad;

	half_fovrad = cam->params.camera.fov * 0.5;
	y = tanf(half_fovrad);
	x = -y * ((float)win->winx / (float)win->winy);
	increment->x = -x / ((float)win->winx / 2.0);
	increment->y = -y / ((float)win->winx / 2.0);
	return (vec_init0(x + (increment->x / 2.0), y + (increment->y / 2.0), 1));
}

t_renderer		*renderer_init(t_obj *cam, t_args *args, t_env *env)
{
	t_renderer	*renderer;

	renderer = (t_renderer*)ft_malloc(sizeof(t_renderer));
	renderer->renderer_mode = args->renderer_mode;
	if (renderer->renderer_mode == NO_RENDERER)
		return (renderer);
	renderer->width = env->win->winx;
	renderer->height = env->win->winy;
	renderer->depth = 1;
	renderer->print_mode = args->print_mode;
	renderer->top_left_vec =
		get_top_left_vec(cam, &(renderer->increment), env->win);
	if (renderer->renderer_mode == STACK)
		return (renderer);
//	renderer->renderer = renderer_malloc(renderer);
	return (renderer);
}

void			renderers_settings(t_args *args, t_env *env)
{
	t_scene		*scenes;
	t_obj		*cameras;

	scenes = env->scene;
	(void)args;
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
//	step_set(SETTINGS);
	if (args->renderer_mode != NO_RENDERER)
		renderers_settings(args, env);
	if (args->verbose_mode == SETTINGS || args->verbose_mode == ALL_VERBOSE)
		verbose_settings(env);
}
