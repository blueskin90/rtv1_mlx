/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:42:05 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 20:34:59 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				free_mlx(void *mlx, t_win *win)
{
	mlx_destroy_image(mlx, win->img->imgptr);
	free(win->img);
	mlx_destroy_window(mlx, win->winptr);
	free(win);
	mlx_destroy(mlx);

}

void				free_cameras(t_obj *cameras, void *mlx)
{
	t_obj			*ptr;
	
	ptr = cameras;
	while (ptr)
	{
		if (ptr->params.camera.renderer)
		{
			mlx_destroy_image(mlx, ptr->params.camera.renderer->img->imgptr);
			free(ptr->params.camera.renderer->img);
			free(ptr->params.camera.renderer->renderer);
			free(ptr->params.camera.renderer);
		}
		cameras = ptr->next;
		free(ptr);
		ptr = cameras;
	}
}

void				free_objs(t_obj *objs)
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

void				free_scenes(t_scene *scenes, void *mlx)
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

void				free_args(t_args *args)
{
	free(args);
}

void				freeenv(t_env *env)
{
	free_args(env->args);
	free_scenes(env->scene, env->mlx);
	free_mlx(env->mlx, env->win);
	free(env);
}

int					key_pressed(int key, t_env *env)
{
	if (key == X_KEY_ESCAPE)
	{
		freeenv(env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int					window_closed(t_env *env)
{
	freeenv(env);
	exit(EXIT_SUCCESS);
	return (0);
}

void				loop(t_args *args, t_env *env)
{
	env->args = args;
	if (args->print_mode != NO_PRINT && args->renderer_mode != NO_RENDERER)
	{
		mlx_hook(env->win->winptr, 2, 0, key_pressed, env);
		mlx_hook(env->win->winptr, 17, 0, window_closed, env);
		mlx_loop(env->mlx);
	}
	if (args->verbose_mode == LOOP || args->verbose_mode == ALL_VERBOSE)
		verbose_loop(args, env);
	freeenv(env);
}
