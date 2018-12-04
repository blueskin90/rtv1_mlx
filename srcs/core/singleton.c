/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:42:16 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 07:14:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_env		**env_getptr(void)
{
	static t_env	*ptr = NULL;
	return (&ptr);
}

t_env				*env_get(void)
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

static t_scene		**scene_getptr(void)
{
	static t_scene	*ptr = NULL;
	return (&ptr);
}

t_scene				*scene_get(void)
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

static t_obj		**camera_getptr(void)
{
	static t_obj	*ptr = NULL;
	return (&ptr);
}

t_obj				*camera_get(void)
{
	return (*(camera_getptr()));
}

static t_ray		*camera_get_renderer(void)
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

t_win				*win_get(void)
{
	return(env_get()->win);
}

int					win_getx(void)
{
	return(env_get()->win->winx);
}

int					win_gety(void)
{
	return(env_get()->win->winy);
}

static t_ray		**renderer_getptr(void)
{
	static t_ray	*ptr = NULL;

	return (&ptr);
}

t_ray				*renderer_getray(int nb)
{
	return (*(renderer_getptr()) + nb);
}

t_ray				*renderer_get()
{
	return (*(renderer_getptr()));
}

int					renderer_getraymax(void)
{
	return (camera_get()->params.camera.raynumber);
}

void				renderer_set(void)
{
	t_ray			**ptr;

	ptr = renderer_getptr();
	if (ptr == NULL)
		printf("renderer_set has a renderer_getptr == null\n");
	*ptr = camera_get_renderer();
}

void				*mlx_get(void)
{
	return(env_get()->mlx); 
}

static int					*print_mode_getptr(void)
{
	static int		mode = 0;
	return (&mode);
}

int					print_mode_get(void)
{
	return (*(print_mode_getptr()));
}

void				print_mode_set(int mode)
{
	*(print_mode_getptr()) = mode;
}


static int			*cursor_getptrx(void)
{
	static int		x = 0;
	return (&x);
}

static int			*cursor_getptry(void)
{
	static int		y = 0;
	return (&y);
}

int					cursor_getx(void)
{
	return (*(cursor_getptrx()));
}

int					cursor_gety(void)
{
	return (*(cursor_getptry()));
}

void				cursor_movex(int x)
{
	int				*xptr;

	xptr = cursor_getptrx();
	if (*xptr + x > win_getx())
		*xptr = *xptr + x - win_getx();
	else if (*xptr + x < 0)
		*xptr = *xptr + x + win_getx();
	else
		*xptr = *xptr + x;
}

void				cursor_movey(int y)
{
	int				*yptr;

	yptr = cursor_getptry();
	if (*yptr + y > win_gety())
		*yptr = *(yptr) + y - win_gety();
	else if (*yptr + y < 0)
		*yptr = *(yptr) + y + win_gety();
	else
		*yptr = *yptr + y;
}

void				cursor_reset(void)
{
	int				*ptr;

	ptr = cursor_getptrx();
	*ptr = 0;
	ptr = cursor_getptry();
	*ptr = 0;
}

static int			*cursor_mode_getptr(void)
{
	static int		mode = 0;
	return (&mode);
}

int					cursor_mode_get(void)
{
	return (*(cursor_mode_getptr()));
}

void				cursor_mode_toggle(void)
{
	*(cursor_mode_getptr()) = (cursor_mode_get() ^ 1);
}

void				cursor_mode_set(int value)
{
	*(cursor_mode_getptr()) = value % 2;
}
