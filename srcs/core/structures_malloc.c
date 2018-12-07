/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/07 19:18:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_vec			vec_x(void)
{
	return (vec_init0(1, 0, 0));
}

t_vec			vec_y(void)
{
	return (vec_init0(0, 1, 0));
}

t_vec			vec_z(void)
{
	return (vec_init0(0, 0, 1));
}

t_matrix	rotmatrix_axis_angle(t_vec axis, float angle)
{
	float	cos;
	float	sin;
	float	t;
	float	tmp1;
	float	tmp2;
	t_matrix	matrix;

	matrix = identity_matrix_init();
	if (angle == 0 || angle == NAN || vec_magnitude(axis) == 0)
		return (matrix);
	cos = cosf(angle);
	sin = sinf(angle);
	t = 1.0 - cos;
	matrix.matrix[0][0] = cos + axis.x * axis.x * t;
	matrix.matrix[1][1] = cos + axis.y * axis.y * t;
	matrix.matrix[2][2] = cos + axis.z * axis.z * t;
	tmp1 = axis.x * axis.y * t;
	tmp2 = axis.z * sin;
	matrix.matrix[1][0] = tmp1 + tmp2;
	matrix.matrix[0][1] = tmp1 - tmp2;
	tmp1 = axis.x * axis.z * t;
	tmp2 = axis.y * sin;
	matrix.matrix[2][0] = tmp1 - tmp2;
	matrix.matrix[0][2] = tmp1 + tmp2;
	tmp1 = axis.y * axis.z * t;
	tmp2 = axis.x * sin;
	matrix.matrix[2][1] = tmp1 + tmp2;
	matrix.matrix[1][2] = tmp1 - tmp2;
	return (matrix);
}

t_matrix		world_to_obj_matrix(t_obj *obj)
{
	t_matrix	matrix;

	matrix = identity_matrix_init();
	matrix.matrix[0][0] = obj->right.x;
	matrix.matrix[0][1] = obj->right.y;
	matrix.matrix[0][2] = obj->right.z;
	matrix.matrix[1][0] = obj->up.x;
	matrix.matrix[1][1] = obj->up.y;
	matrix.matrix[1][2] = obj->up.z;
	matrix.matrix[2][0] = obj->dir.x;
	matrix.matrix[2][1] = obj->dir.y;
	matrix.matrix[2][2] = obj->dir.z;
//	matrix.matrix[0][3] = obj->pos.x;
//	matrix.matrix[1][3] = obj->pos.y;
//	matrix.matrix[2][3] = obj->pos.z;
	return (matrix);
}

t_matrix		obj_to_world_matrix(t_obj *obj)
{
	t_matrix	matrix;

	matrix = obj->world_to_obj;
	matrix.matrix[0][1] = obj->world_to_obj.matrix[1][0];
	matrix.matrix[0][2] = obj->world_to_obj.matrix[2][0];
	matrix.matrix[0][3] = obj->world_to_obj.matrix[3][0];
	matrix.matrix[1][0] = obj->world_to_obj.matrix[0][1];
	matrix.matrix[1][2] = obj->world_to_obj.matrix[2][1];
	matrix.matrix[1][3] = obj->world_to_obj.matrix[3][1];
	matrix.matrix[2][0] = obj->world_to_obj.matrix[0][2];
	matrix.matrix[2][1] = obj->world_to_obj.matrix[1][2];
	matrix.matrix[2][3] = obj->world_to_obj.matrix[3][2];
//	matrix.matrix[3][0] = obj->world_to_obj.matrix[0][3];
//	matrix.matrix[3][1] = obj->world_to_obj.matrix[1][3];
//	matrix.matrix[3][2] = obj->world_to_obj.matrix[2][3];
	return (matrix);
}

t_obj			*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_RGB c)
{
	return (obj_malloc_dir(pos, vec_sub(lookat, pos), up, c));
}

t_vec			get_rightdir(t_vec dir)
{
	if (is_equal_vec(dir, vec_y()))
		return (vec_x());
	else if (is_equal_vec(dir, vec_opposite(vec_y())))
		return (vec_x());
	return (vec_normalize(vec_opposite(vec_crossproduct(dir, vec_y()))));
}

t_vec			get_updir(t_vec dir, t_vec right)
{
	return (vec_crossproduct(dir, right));
}

t_obj			*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_RGB c)
{
	t_obj		*obj;

	obj = (t_obj*)ft_malloc(sizeof(t_obj));
	obj->pos = pos;
	obj->dir = vec_normalize(dir);
	obj->right = get_rightdir(obj->dir);
	obj->up = get_updir(obj->dir, obj->right);
//	obj->dir = vec_opposite(obj->dir);
//	obj->right = vec_opposite(obj->right);
	obj->color = c;
	obj->world_to_obj = world_to_obj_matrix(obj);
	obj->obj_to_world = obj_to_world_matrix(obj);
	return (obj);
}

void			obj_sphere_params(t_obj *obj, float radius)
{
	obj->params.sphere.radius = radius;
	obj->type = SPHERE;
	obj->intersect = &sphere_intersection;
}

void			obj_cylinder_params(t_obj *obj, float radius)
{
	obj->params.cylinder.radius = radius;
	obj->type = CYLINDER;
	obj->intersect = &cylinder_intersection;
}

void			obj_plane_params(t_obj *obj)
{
	obj->type = PLANE;
	obj->intersect = &plane_intersection;
}

void			obj_cone_params(t_obj *obj, float angle)
{
	obj->params.cone.angle = degtorad(angle);
	obj->type = CONE;
	obj->intersect = &cone_intersection;
}

void			obj_camera_params(t_obj *obj, float fov)
{
	obj->params.camera.fov = degtorad(fov);
	obj->type = CAMERA;
	renderer_malloc(obj);
}

void			obj_light_params(t_obj *obj, float intensity)
{
	obj->params.light.intensity = intensity;
	obj->type = LIGHT;
}

t_vec		get_top_left_vec(t_obj *cam, t_vec *increment)
{
	float		x;
	float		y;
	float		half_fovrad;

	half_fovrad = cam->params.camera.fov * 0.5;
	y = tanf(half_fovrad);
	x = -y * ((float)win_getx() / (float)win_gety());
	increment->x = -x / ((float)win_getx() / 2.0);
	increment->y = -y / ((float)win_gety() / 2.0);

	return (vec_init0(x + (increment->x / 2.0), y + (increment->y / 2.0), 1));
}

t_vec			get_actual_dir(t_vec topleft, t_vec inc, int x, int y)
{
	t_vec		final;

	final = vec_init0(topleft.x + x * inc.x, topleft.y + y * inc.y, 1);
	final = vec_normalize(final);
	return (final);
}

// on se deplace, puis on rotate sur NOUS MEMES


// prendre en compte l'antialiasing
void			renderer_malloc(t_obj *camera)
{
	t_vec		increment;
	t_vec		topleft;
	int			x;
	int			y;
	t_ray		ray;

	camera->params.camera.rays = (t_ray*)ft_malloc(sizeof(t_ray) * win_getx() * win_gety());
	camera->params.camera.raynumber = win_getx() * win_gety();
	increment = vec_init0(0, 0, 0);
	topleft = get_top_left_vec(camera, &increment);
	ft_bzero(&ray, sizeof(t_ray));
	ray.pos = camera->pos;
	ray.length = INFINITY;
	y = 0;
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			ray.dir = vec_norm(get_actual_dir(topleft, increment, x, y));
			ray.dir = vec_norm(matrix_mult_vec(camera->obj_to_world, ray.dir));
			camera->params.camera.rays[x + y * win_getx()] = ray;
			x++;
		}
		y++;
	}
}
