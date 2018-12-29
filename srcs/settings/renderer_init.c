/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 22:21:06 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 02:17:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_vec			get_actual_dir(t_vec topleft, t_vec inc, int x, int y)
{
	t_vec		final;

	final = vec_init0(topleft.x + x * inc.x, topleft.y + y * inc.y, topleft.z);
	final = vec_normalize(final);
	return (final);
}

t_ray			get_actual_ray(t_renderer *renderer, t_obj *cam, int x, int y)
{
	t_ray		ray;
	t_vec		dir;

	dir = get_actual_dir(renderer->top_left_vec, renderer->increment, x, y);
	ray = ray_init(vec_init0(0, 0, 0), dir);
	ray = ray_to_world(ray, cam);
	return (ray);	
}

static t_vec		get_top_left_vec(t_obj *cam, t_vec *increment, t_win *win)
{
	float		x;
	float		y;
	float		half_fovrad;

	half_fovrad = cam->params.camera.fov * 0.5;
	y = tanf(half_fovrad);
	x = -y * ((float)win->winx / (float)win->winy);
	increment->x = -x / ((float)win->winx / 2.0);
	increment->y = -y / ((float)win->winy / 2.0);
	return (vec_init0(x + (increment->x / 2.0), y + (increment->y / 2.0), 1));
}

t_ray			*renderer_malloc(t_renderer *renderer, t_obj *cam)
{
	t_ray		*rays;
	int			x;
	int			y;
	int			ray;

	rays = (t_ray*)ft_malloc(sizeof(t_ray) *
			(renderer->width * renderer->height * renderer->depth));
	y = 0;
	ray = 0;
	while (y < renderer->height)
	{
		x = 0;
		while (x < renderer->width)
		{
			rays[ray] = get_actual_ray(renderer, cam, x, y);
			ray++;
			x++;
		}
		y++;
	}
	return (rays);
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
	renderer->img = img_init(env->win->winx, env->win->winy, env->mlx);
	if (renderer->renderer_mode == STACK) 
		return (renderer);
	renderer->renderer = renderer_malloc(renderer, cam);
	return (renderer);
}
