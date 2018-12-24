/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 22:02:16 by toliver          ###   ########.fr       */
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

t_matrix		rotmatrix_axis_angle(t_vec axis, float angle)
{
	float		cos;
	float		sin;
	float		t;
	float		tmp1;
	float		tmp2;
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
	t_vec		zaxis;
	t_vec		yaxis;
	t_vec		xaxis;

	zaxis = obj->dir;
	xaxis = obj->right;
	yaxis = obj->up;
	matrix = identity_matrix_init();
	matrix.matrix[0][0] = xaxis.x;
	matrix.matrix[0][1] = xaxis.y;
	matrix.matrix[0][2] = xaxis.z;
	matrix.matrix[1][0] = yaxis.x;
	matrix.matrix[1][1] = yaxis.y;
	matrix.matrix[1][2] = yaxis.z;
	matrix.matrix[2][0] = zaxis.x;
	matrix.matrix[2][1] = zaxis.y;
	matrix.matrix[2][2] = zaxis.z;
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
	matrix.matrix[3][0] = obj->world_to_obj.matrix[0][3];
	matrix.matrix[3][1] = obj->world_to_obj.matrix[1][3];
	matrix.matrix[3][2] = obj->world_to_obj.matrix[2][3];
	return (matrix);
}

t_obj			*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_RGB c)
{
	t_obj		*obj;

	obj = obj_malloc_dir(pos, vec_sub(lookat, pos), up, c);
	obj->lookat = lookat;
	return (obj);
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
	return (vec_norm(vec_crossproduct(dir, right)));
}

t_obj			*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_RGB c)
{
	t_obj		*obj;

	(void)up;
	obj = (t_obj*)ft_malloc(sizeof(t_obj));
	obj->pos = pos;
	obj->dir = vec_normalize(dir);
	obj->right = get_rightdir(obj->dir);
	obj->up = get_updir(obj->dir, obj->right);
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
	obj->params.camera.rays = NULL;
	obj->params.camera.raynumber = 0;
}

void			obj_light_params(t_obj *obj, float intensity)
{
	obj->params.light.intensity = intensity;
	obj->type = LIGHT;
}

void			renderer_malloc(t_obj *camera)
{
	t_vec		increment;
	t_vec		topleft;
	int			x;
	int			y;
	t_ray		ray;

	camera->params.camera.rays = (t_ray*)ft_malloc(sizeof(t_ray) * win_getx()
			* win_gety());
	camera->params.camera.raynumber = win_getx() * win_gety();
	increment = vec_init0(0, 0, 0);
	topleft = get_top_left_vec(camera, &increment);
	ft_bzero(&ray, sizeof(t_ray));
	ray.pos = vec_init0(0, 0, 0);
	ray.length = INFINITY;
	y = -1;
	while (++y < win_gety())
	{
		x = -1;
		while (++x < win_getx())
		{
			ray.dir = vec_norm(get_actual_dir(topleft, increment, x, y));
			camera->params.camera.rays[x + y * win_getx()] =
				ray_to_world(ray, camera);
		}
	}
}

void			malloc_renderers(void)
{
	t_obj		*cam;
	t_scene		*scene;

	scene = env_get()->scene;
	while (scene)
	{
		cam = scene->cameras;
		while (cam)
		{
			renderer_malloc(cam);
			cam = cam->next;
		}
		scene = scene->next;
	}
}
