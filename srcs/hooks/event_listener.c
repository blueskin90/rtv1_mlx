/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 18:01:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec	vec_init_origin()
{
	return (vec_init0(0, 0, 0));
}

t_vec	vec_left()
{
	return (vec_init0(-1, 0, 0));
}

t_vec	vec_right()
{
	return (vec_init0(1, 0, 0));
}

t_vec	vec_forward()
{
	return (vec_init0(0, 0, 1));
}

t_vec	vec_backward()
{
	return (vec_init0(0, 0, -1));
}

t_vec	vec_up()
{
	return (vec_init0(0, 1, 0));
}

t_vec	vec_down()
{
	return (vec_init0(0, -1, 0));
}

void	pos_notify(int x, int y, t_env *env)
{
/*	printf("------------------\n");
	printf("x : %d y : %d\n", x, y);
///	ft_printf("xx : %d yy : %d\n", cam_to_world_x((double)x, env), 
//			cam_to_world_y((double)y, env));
	printf("------------------\n");*/
}

int				move(int key, t_env *env)
{
	t_vec	dir;

	dir = vec_init_origin();
	if (key == X_KEY_A)
	{
		dir = vec_add(dir, vec_opposite(env->camera->right));
	}
	if (key == X_KEY_D)
	{
		dir = vec_add(dir, env->camera->right);
	}
	if (key == X_KEY_W)
	{
		dir = vec_add(dir, env->camera->orientation);
	}
	if (key == X_KEY_S)
	{
		dir = vec_add(dir, vec_opposite(env->camera->orientation));
	}
	if (key == X_KEY_SPACE)
	{
		dir = vec_add(dir, env->camera->top);
	}
	if (key == X_KEY_L_CTRL)
	{
		dir = vec_add(dir, vec_opposite(env->camera->top));
	}
	dir = vec_normalize(dir);
	env->camera->pos = vec_add(env->camera->pos, dir);
	world_to_cam2(env->camera, env->scene, env->scene_copy);
	raytracing(env);
	return (1);
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

t_vec		rotate_vec_angle(t_vec vec, float xangle, float yangle, float zangle)
{
	t_matrix	matrix;

	matrix = matrix_mult(rotx_matrix_init(xangle), roty_matrix_init(yangle));
	matrix = matrix_mult(matrix, rotz_matrix_init(zangle));
	return (matrix_mult_vec(matrix, vec));
}

int		mousemove(int x, int y, t_env *env)
{
	static	int oldx = INT_MIN;
	static	int	oldy = INT_MIN;
	float	xinc;
	float	yinc;
	
	xinc = 0;
	yinc = 0;
	if (oldx == INT_MIN)
	{
		oldx = x;
		oldy = y;
	}
	else
	{
		xinc = ((float)(x - oldx)) / 10.0;
		yinc = ((float)(y - oldy)) / 10.0;
		env->camera->rotx -= yinc;
		env->camera->roty -= xinc;
		env->camera->orientation = rotate_vec_angle(env->camera->orientation, yinc, xinc, 0);
		env->camera->top = rotate_vec_angle(env->camera->top, yinc, xinc, 0);
		env->camera->right = rotate_vec_angle(env->camera->right, yinc, xinc, 0);
		oldx = x;
		oldy = y;	
		world_to_cam2(env->camera, env->scene, env->scene_copy);
		raytracing(env);
	}
	return (1);
}

void		events_listener(t_env *env)
{
//	printf("%d", X_KEYPRESS)vec_init(cam->pos, original->pos), ;
//	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win->winptr, X_MOTIONNOTIFY, 0, mousemove, env); 
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, keypressed, env);
//	mlx_hook(env->win, X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, env);

}
