/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 21:30:55 by toliver           #+#    #+#             */
/*   Updated: 2019/01/05 00:44:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void			free_mlx(void *mlx, t_win *win)
{
	if (win)
	{
		if (win->img)
		{
			mlx_destroy_image(mlx, win->img->imgptr);
			free(win->img);
		}
		mlx_destroy_window(mlx, win->winptr);
		free(win);
		mlx_destroy(mlx);
	}
}

static void			free_cameras(t_obj *cameras, void *mlx)
{
	t_obj			*ptr;

	ptr = cameras;
	while (ptr)
	{
		if (ptr->params.camera.renderer)
		{
			if (mlx)
				mlx_destroy_image(mlx,
						ptr->params.camera.renderer->img->imgptr);
			free(ptr->params.camera.renderer->img);
			free(ptr->params.camera.renderer->renderer);
			free(ptr->params.camera.renderer);
		}
		cameras = ptr->next;
		free(ptr);
		ptr = cameras;
	}
}

static void			free_objs(t_obj *objs)
{
	t_obj			*ptr;

	ptr = objs;
	while (ptr)
	{
		objs = ptr->next;
		free(ptr);
		ptr = objs;
	}
}

static void			free_scenes(t_scene *scenes, void *mlx)
{
	t_scene			*ptr;

	ptr = scenes;
	while (ptr)
	{
		free(ptr->name);
		free_objs(ptr->objs);
		free_objs(ptr->lights);
		free_cameras(ptr->cameras, mlx);
		scenes = ptr->next;
		free(ptr);
		ptr = scenes;
	}
}

void				free_env(t_env *env)
{
	free(env->args);
	free_scenes(env->scene, env->mlx);
	free_mlx(env->mlx, env->win);
	free(env);
}
