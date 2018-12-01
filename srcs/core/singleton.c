/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:42:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/01 15:08:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_env		**env_getptr()
{
	static t_env	*ptr = NULL;
	return (&ptr);
}

t_env				*env_get()
{
	return (*(env_getptr()));
}

void				env_set(t_env *env)
{
	t_env			**ptr;

	ptr = env_getptr();
	if (ptr == NULL)
	printf("env_set has a env_getptr == null\n");
	*ptr = env;
}

static t_scene		**scene_getptr()
{
	static t_scene	*ptr = NULL;
	return (&ptr);
}

t_scene				*scene_get()
{
	return (*(scene_getptr()));
}

void				scene_set(t_scene *scene)
{
	t_scene			**ptr;

	ptr = scene_getptr();
	if (ptr == NULL)
		printf("scene_set has a scene_getptr == null\n");
	*ptr = scene;
}

static t_obj		**camera_getptr()
{
	static t_obj	*ptr = NULL;
	return (&ptr);
}

t_obj				*camera_get()
{
	return (*(camera_getptr()));
}

static t_ray		*camera_get_renderer()
{
	return (camera_get()->params.camera.rays);
}

void				camera_set(t_obj *camera)
{
	t_obj			**ptr;

	ptr = camera_getptr();
	if (ptr == NULL)
		printf("camera_set has a camera_getptr == null\n");
	*ptr = camera;
}

t_win				*win_get()
{
	return(env_get()->win);
}

int					win_getx()
{
	return(env_get()->win->winx);
}

int					win_gety()
{
	return(env_get()->win->winy);
}

static t_ray		**renderer_getptr()
{
	static t_ray	*ptr = NULL;

	return (&ptr);
}

t_ray				*renderer_getray(int nb)
{
	return (renderer_get() + nb);
}

t_ray				*renderer_get()
{
	return (*(renderer_getptr()));
}

int					renderer_getraymax()
{
	return (camera_get()->params.camera.raynumber);
}

void				renderer_set()
{
	t_ray			**ptr;

	ptr = renderer_getptr();
	if (ptr == NULL)
		printf("renderer_set has a renderer_getptr == null\n");
	*ptr = camera_get_renderer();
}

void				*mlx_get()
{
	return(env_get()->mlx); 
}
