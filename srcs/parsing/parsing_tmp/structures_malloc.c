/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:37:53 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_obj			*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_rgb c)
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

t_obj			*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_rgb c)
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
	obj->params.camera.renderer = NULL;
}

void			obj_light_params(t_obj *obj, float intensity)
{
	obj->params.light.intensity = intensity;
	obj->type = LIGHT;
}
