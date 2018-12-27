/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 05:52:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				quadratic(float a, float b, float c, float l[2])
{
	float		d;

	if (a == 0.0)
		return (0);
	d = b * b - 4 * a * c;
	if (d < TOLERANCE)
		return (0);
	d = sqrtf(d);
	l[0] = (-b + d) / (2 * a);
	l[1] = (-b - d) / (2 * a);
	return (2);
}

float			sphere_radius(t_obj *sphere)
{
	return (sphere->params.sphere.radius);
}

float			sphere_intersection(t_ray ray, t_obj *sphere)
{
	t_vec		origin_to_sphere;
	float		length;
	float		proj_to_center;

	origin_to_sphere = vec_init(ray.pos, sphere->pos);
	length = vec_dotproduct(ray.dir, origin_to_sphere); // projette le centre de la sphere sur le vecteur de rayon et retourne la longueur
	if (length <= 0) // attention si la sphere est derriere et assey grande pour etre vue de l'interieur ?
		return (INFINITY);
	else
	{
		proj_to_center = powf(vec_magnitude(origin_to_sphere), 2) - powf(length, 2);
		proj_to_center = (proj_to_center < 0) ? sqrtf(-proj_to_center) : sqrtf(proj_to_center);
		if (is_equal_float(proj_to_center, sphere_radius(sphere)))
			return (length - TOLERANCE);
		if (proj_to_center > sphere_radius(sphere))
			return (INFINITY);
		return (length - (sqrtf(powf(sphere_radius(sphere), 2) - powf(proj_to_center, 2))) - TOLERANCE);
	}
	return (INFINITY);
}

float			plane_intersection(t_ray ray, t_obj *plane)
{
	float		denom;
	float		length;
	t_vec		diff;

	diff = vec_sub(ray.pos, plane->pos);
//	diff = ray.pos;
	denom = vec_dotproduct(ray.dir, plane->dir);
	if (denom != 0)
	{
		length = -vec_dotproduct(diff, plane->dir) / denom;
		if (length > TOLERANCE)
			return (length - TOLERANCE);
	}
	return (INFINITY);
}

float			cylinder_intersection(t_ray ray, t_obj *cylinder)
{
	float		a;
	float		b;
	float		c;

	float		l[2];
	t_vec		v1;
	t_vec		v2;

	ray = ray_to_obj(ray, cylinder);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - cylinder->params.cylinder.radius * cylinder->params.cylinder.radius;
	if (!quadratic(a, b, c, l))
		return (INFINITY);
	v1 = vec_mul(ray.dir, l[0]);
	v2 = vec_mul(ray.dir, l[1]);
	if (l[0] <= TOLERANCE)
	{
		if (l[1] <= TOLERANCE)
			return (INFINITY);
		return (vec_magnitude(v2) - TOLERANCE);
	}
	if (l[1] <= TOLERANCE)
		return (vec_magnitude(v1) - TOLERANCE);
	if (l[0] < l[1])
		return (vec_magnitude(v1) - TOLERANCE);
	return (vec_magnitude(v2) - TOLERANCE);
}

float			cone_intersection(t_ray ray, t_obj *cone)
{
	float		a;
	float		b;
	float		c;
	float		d;

	float		l[2];
	t_vec		v1;
	t_vec		v2;
	float		tansquare;

	ray.pos = ray_to_obj(ray, cone).pos;
	ray.dir = ray_to_obj(ray, cone).dir;
	tansquare = tanf(cone->params.cone.angle);
	tansquare *= tansquare;
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y - ray.dir.z * ray.dir.z * tansquare;
	b = 2 * ray.pos.x * ray.dir.x + 2 * ray.pos.y * ray.dir.y - 2 * ray.pos.z * ray.dir.z * tansquare;
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y - ray.pos.z * ray.pos.z * tansquare;
	d = b * b - 4 * a * c;
	if (!quadratic(a, b, c, l))
		return (INFINITY);
	v1 = vec_mul(ray.dir, l[0]);
	v2 = vec_mul(ray.dir, l[1]);
	if (l[0] <= TOLERANCE)
	{
		if (l[1] <= TOLERANCE)
			return (INFINITY);
		return (vec_magnitude(v2) - TOLERANCE);
	}
	if (l[1] <= TOLERANCE)
		return (vec_magnitude(v1) - TOLERANCE);
	if (l[0] < l[1])
		return (vec_magnitude(v1) - TOLERANCE);
	return (vec_magnitude(v2) - TOLERANCE);
}

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
	obj->params.camera.renderer = NULL;
}

void			obj_light_params(t_obj *obj, float intensity)
{
	obj->params.light.intensity = intensity;
	obj->type = LIGHT;
}
