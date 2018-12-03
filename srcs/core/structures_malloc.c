/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 04:41:58 by toliver          ###   ########.fr       */
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

t_matrix	rotmatrix_axis_angle(t_vec v, float angle)
{
	t_matrix	matrix;
	float		cos;
	float		sin;

	if (angle == 0.0 || angle == NAN || vec_magnitude(v) < TOLERANCE)
		return (identity_matrix_init());
	cos = cosf(angle);
	sin = sinf(angle);
	matrix.matrix[0][0] = cos + v.x * v.x * (1 - cos);
	matrix.matrix[0][1] = v.x * v.y * (1 - cos) - v.z * sin;
	matrix.matrix[0][2] = v.x * v.z * (1 - cos) + v.y * sin;
	matrix.matrix[0][3] = 0;
	matrix.matrix[1][0] = v.y * v.x * (1 - cos) + v.z * sin;
	matrix.matrix[1][1] = cos + v.y * v.y * (1 - cos);
	matrix.matrix[1][2] = v.y * v.z * (1 - cos) - v.x * sin;
	matrix.matrix[1][3] = 0;
	matrix.matrix[2][0] = v.z * v.x * (1 - cos) - v.y * sin;
	matrix.matrix[2][1] = v.z * v.y * (1 - cos) + v.x * sin; 
	matrix.matrix[2][2] = cos + v.z * v.z * (1 - cos);
	matrix.matrix[2][3] = 0;
	matrix.matrix[3][0] = 0; 
	matrix.matrix[3][1] = 0;
	matrix.matrix[3][2] = 0;
	matrix.matrix[3][3] = 1;
	return (matrix);
}

t_matrix		world_to_obj_matrix(t_obj *obj)
{
	t_matrix	matrix;
	t_vec		axis;
	float		angle;

	axis = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, vec_z())));
	angle = acos(vec_dotproduct(obj->dir, vec_z()));
	if (vec_magnitude(axis) == 0)
		return (identity_matrix_init());
	matrix = rotmatrix_axis_angle(axis, angle);
	return (matrix);
}

t_matrix		obj_to_world_matrix(t_obj *obj)
{
	t_matrix	matrix;
	t_vec		axis;
	float		angle;

	axis = vec_normalize(vec_opposite(vec_crossproduct(obj->dir, vec_z())));
	angle = acos(vec_dotproduct(obj->dir, vec_z()));
	if (vec_magnitude(axis) == 0)
		return (identity_matrix_init());
	matrix = rotmatrix_axis_angle(axis, -angle);
	return (matrix);
}

t_obj			*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_color c)
{
	return (obj_malloc_dir(pos, vec_sub(lookat, pos), up, c));
}

t_obj			*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_color c)
{
	t_obj		*obj;

	obj = (t_obj*)ft_malloc(sizeof(t_obj));
	obj->pos = pos;
	obj->dir = vec_normalize(dir);
	obj->up = up;
	obj->color = c;
	obj->world_to_obj = world_to_obj_matrix(obj);
	obj->obj_to_world = obj_to_world_matrix(obj);
	return (obj);
}

	 // accelerer ca, en ne calculant qu'une fois l'angle le vecteur et tout pour la matrice de rotation;
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
			ray.dir = vec_norm(matrix_mult_vec(camera->world_to_obj, ray.dir));
			camera->params.camera.rays[x + y * win_getx()] = ray;
			x++;
		}
		y++;
	}
}
