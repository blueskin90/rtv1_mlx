/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/11 20:28:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	vec_initO_ver(t_vertex a)
{
	return (vector_init(vertex_init(0, 0, 0), a));
}

t_vector	vec_initO_int(float x, float y, float z)
{
	t_vector	retval;

	retval.x = x;
	retval.y = y;
	retval.z = z;
	retval.w = 0;
	return (retval);
}

t_vector	vec_init_origin()
{
	return (vec_initO_int(0, 0, 0));
}

t_vector	vec_left()
{
	return (vec_initO_int(-1, 0, 0));
}

t_vector	vec_right()
{
	return (vec_initO_int(1, 0, 0));
}

t_vector	vec_forward()
{
	return (vec_initO_int(0, 0, 1));
}

t_vector	vec_backward()
{
	return (vec_initO_int(0, 0, -1));
}

t_vector	vec_up()
{
	return (vec_initO_int(0, 1, 0));
}

t_vector	vec_down()
{
	return (vec_initO_int(0, -1, 0));
}

t_vector	vec_add(t_vector a, t_vector b)
{
	return (vector_add(a, b));
}

t_vector	vec_normalize(t_vector a)
{
	return (vector_normalize(a));
}

void	pos_notify(int x, int y, t_env *env)
{
/*	printf("------------------\n");
	printf("x : %d y : %d\n", x, y);
///	ft_printf("xx : %d yy : %d\n", cam_to_world_x((double)x, env), 
//			cam_to_world_y((double)y, env));
	printf("------------------\n");*/
}

t_vertex		vertex_add_vector(t_vertex a, t_vector b)
{
	t_vertex	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = 1;
	return (c);
}

int				move(int key, t_env *env)
{
	t_vector	dir;

	dir = vec_init_origin();
	if (key == X_KEY_A)
		dir = vec_add(dir, vec_left());
	if (key == X_KEY_D)
		dir = vec_add(dir, vec_right());
	if (key == X_KEY_W)
		dir = vec_add(dir, vec_forward());
	if (key == X_KEY_S)
		dir = vec_add(dir, vec_backward());
	if (key == X_KEY_SPACE)
		dir = vec_add(dir, vec_up());
	if (key == X_KEY_L_CTRL)
		dir = vec_add(dir, vec_down());
	dir = vec_normalize(dir);
	env->camera->pos = vertex_add_vector(env->camera->pos, dir);
	world_to_cam2(env->camera, env->scene, env->scene_copy);
	raytracing(env);
	return (1);
//	raytracing(env);
}

int		keypressed(int key, t_env *env)
{
	if (key == X_KEY_ESCAPE)
	{
		//freeenv(env);
		exit(EXIT_SUCCESS);
	}
	if (key == X_KEY_A || key == X_KEY_D || key == X_KEY_W || key == X_KEY_S
			|| key == X_KEY_SPACE || key == X_KEY_L_CTRL)
		return (move(key, env));
	return 0;
}

int		mousemove(int x, int y, t_env *env)
{
	static	int oldx = INT_MIN;
	static	int	oldy = INT_MIN;
	int		xinc;
	int		yinc;

	xinc = 0;
	yinc = 0;
	if (oldx == INT_MIN)
	{
		oldx = x;
		oldy = y;
	}
	else
	{
		xinc = x - oldx;
		yinc = y - oldy;
//		printf("x %d xinc %d, y %d yinc %d\n", x, xinc,  y, yinc);
	}
	return (1);
}

void		events_listener(t_env *env)
{
//	printf("%d", X_KEYPRESS);
//	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win->winptr, X_MOTIONNOTIFY, 0, mousemove, env); 
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, keypressed, env);
//	mlx_hook(env->win, X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, env);

}
