/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 02:43:36 by toliver          ###   ########.fr       */
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
	env->camera->lookat = vec_add(env->camera->lookat, dir);
//	world_to_cam2(env->camera, env->scene, env->scene_copy);
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

void	make_quat(float quat[4], t_vec v2, float angle)
{
	t_vec	axis;
	float	rl;
	float	ca;
	float	cq;
	float	sq;

	axis = vec_init0(v2.x, v2.y, v2.z);
	rl = sqrtf(vec_dotproduct(axis, axis));
	if (rl < TOLERANCE)
	{
		quat[0] = 0.0;
		quat[1] = 0.0;
		quat[2] = 0.0;
		quat[3] = 1.0;
		return;
	}
	ca = cosf(angle);
	if (ca < -1.0)
		ca = -1.0;
	else if (ca > 1.0)
		ca = 1.0;
	cq = sqrtf((1.0 + ca) / 2.0);
	sq = sqrtf((1.0 - ca) / 2.0);
	axis = vec_mul(axis, sq / rl);
	quat[0] = axis.x;
	quat[1] = axis.y;
	quat[2] = axis.z;
	quat[3] = cq;
}

void	qmul(float r[4], float q[4], float p[4])
{
	float	w0;
	float	w1;
	float	x0;
	float	x1;
	float	y0;
	float	y1;
	float	z0;
	float	z1;
	
	w0 = q[3];
	w1 = p[3];	
	x0 = q[0];
	x1 = p[0];
	y0 = q[1];
	y1 = p[1];
	z0 = q[2];
	z1 = p[2];

	r[3] = w0 * w1 - x0 * x1 - y0 * y1 - z0 * z1;
	r[0] = w0 * x1 + x0 * w1 + y0 * z1 - z0 * y1;
	r[1] = w0 * y1 + y0 * w1 + z0 * x1 - x0 * z1;
	r[2] = w0 * z1 + z0 * w1 + x0 * z1 - z0 * x1;
}

t_vec	qrot(t_vec v, float q[4])
{
	float	r[4];
	float	p[4];
	t_vec	v2;

	r[0] = v.x;
	r[1] = v.y;
	r[2] = v.z;
	r[3] = 0.0;
	qmul(r, q, r);
	p[0] = -q[0];
	p[1] = -q[1];
	p[2] = -q[2];
	p[3] = q[3];
	qmul(r, r, p);
	v2 = vec_init0(r[0], r[1], r[2]);
	return (v2);
}

int		mousemove(int x, int y, t_env *env)
{
	static	int oldx = INT_MIN;
	static	int	oldy = INT_MIN;
	float	xinc;
	float	yinc;
	t_matrix	matrix;
	xinc = 0;
	yinc = 0;
	if (oldx == INT_MIN)
	{
		oldx = x;
		oldy = y;
	}
	else
	{
//		xinc = ((float)(x - oldx)) / 10;
//		yinc = ((float)(y - oldy)) / 10;
//		env->camera->rotx -= yinc;
//		env->camera->roty -= xinc;
//		env->camera->orientation = matrix_mult_vec(roty_matrix_init(xinc), env->camera->orientation);
//		env->camera->right = matrix_mult_vec(roty_matrix_init(xinc), env->camera->right);
//		make_quat(q, env->camera->right, degtorad(yinc));
//		env->camera->orientation = qrot(env->camera->orientation, q);
//		env->camera->top = qrot(env->camera->top, q);
//		make_quat(q, env->camera->orientation, degtorad(0));
//		env->camera->top = qrot(env->camera->top, q);
//		env->camera->right = qrot(env->camera->right, q);
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
