/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:01:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/28 19:31:44 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix		world_to_obj(t_obj *obj)
{
	obj->world_to_obj_vec =  vec_normalize(vec_opposite(vec_crossproduct(obj->rot, vec_init0(0,0,1))));
	obj->world_to_obj_angle = -acos(vec_dotproduct(obj->rot, vec_init0(0, 0, 1)));
	if (vec_magnitude(obj->world_to_obj_vec) == 0)
		return (identity_matrix_init());
	return (rotmatrix_axis_angle(obj->world_to_obj_vec, obj->world_to_obj_angle));
}

t_matrix		obj_to_world(t_obj *obj)
{
	obj->obj_to_world_vec =  vec_normalize(vec_opposite(vec_crossproduct(obj->rot, vec_init0(0,0,1))));
	obj->obj_to_world_angle = acos(vec_dotproduct(obj->rot, vec_init0(0, 0, 1)));
	if (vec_magnitude(obj->world_to_obj_vec) == 0)
		return (identity_matrix_init());
	return (rotmatrix_axis_angle(obj->world_to_obj_vec, obj->world_to_obj_angle));
}

t_obj			*plane_malloc(t_vec p, t_vec lookat, t_color c)
{
	t_obj		*plane;

	plane = (t_obj*)ft_malloc(sizeof(t_obj));
	plane->pos = p;
	plane->params.plane.lookat = lookat;
	plane->params.plane.normal = vec_norm(vec_init(p, lookat));
	plane->rot = plane->params.plane.normal;
	plane->color = c;
	plane->type = PLANE;
	plane->intersect = &plane_intersection;
	plane->world_to_obj = world_to_obj(plane);
	plane->obj_to_world = obj_to_world(plane);
	plane->next = NULL;
	return (plane);
}

t_obj			*sphere_malloc(t_vec p, float rad, t_vec r, t_color c)
{
	t_obj		*sphere;

	sphere = (t_obj*)ft_malloc(sizeof(t_obj));
	sphere->pos = p;
	sphere->params.sphere.radius = rad;
	sphere->rot = r;
	sphere->color = c;
	sphere->type = SPHERE;
	sphere->intersect = &sphere_intersection;
	sphere->world_to_obj = world_to_obj(sphere);
	sphere->obj_to_world = obj_to_world(sphere);
	sphere->next = NULL;
	return (sphere);
}

t_obj			*cylinder_malloc(t_vec p, float rad, t_vec lookat, t_color c)
{
	t_obj		*cylinder;

	cylinder = (t_obj*)ft_malloc(sizeof(t_obj));
	cylinder->pos = p;
	cylinder->params.cylinder.radius = rad;
	cylinder->params.cylinder.lookat = lookat;
	cylinder->params.cylinder.axis = vec_normalize(vec_init(p, lookat));
	cylinder->rot = cylinder->params.cylinder.axis;
	cylinder->color = c;
	cylinder->type = CYLINDER;
	cylinder->intersect = &cylinder_intersection;
	cylinder->world_to_obj = world_to_obj(cylinder);
	cylinder->obj_to_world = obj_to_world(cylinder);
	cylinder->next = NULL;
	return (cylinder);
}

t_obj			*cone_malloc(t_vec p, float angle, t_vec lookat, t_color c)
{
	t_obj		*cone;

	cone = (t_obj*)ft_malloc(sizeof(t_obj));
	cone->pos = p;
	cone->params.cone.lookat = lookat;
	cone->params.cone.angle = angle;// a voir si je degtorad ici ou a linit
	cone->params.cone.axis = vec_normalize(vec_init(p, lookat));
	cone->rot = cone->params.cone.axis;
	cone->color = c;
	cone->type = CONE;
	cone->intersect = &cone_intersection;
	cone->world_to_obj = world_to_obj(cone);
	cone->obj_to_world = obj_to_world(cone);
	printf("cone pos :");
	print_vec(cone->pos);
	printf("cone axis :");
	print_vec(cone->rot);
	printf("cone world rot axis :");
	print_vec(cone->world_to_obj_vec);
	printf("angle = %f\n", radtodeg(cone->world_to_obj_angle));
	cone->next = NULL;
	return (cone);
}

t_vec				get_top_vector(t_vec orientation)
{
	t_vec			axis;
	float			angle;
	t_matrix		matrix;

	angle = vec_dotproduct(orientation, vec_init0(0,1,0));
	if (!isequalfloat(angle, 0.0) && !isequalfloat(fabs(angle), 1.0))
		angle = acosf(angle);
	else if (isequalfloat(angle, 1.0))
		angle = 0;
	else if (isequalfloat(angle, -1))
		angle = degtorad(180);
	else
		angle = degtorad(90);
	angle = degtorad(90) - angle;
	if (isequalfloat(angle, 0.0))
		return (vec_init0(0,1,0));
	axis = vec_crossproduct(orientation, vec_init0(0,1,0));
	matrix = rotmatrix_axis_angle(axis, -angle);
	return (matrix_mult_vec(matrix, vec_init0(0,1,0)));
}

t_camera			*camera_malloc(t_vec pos, t_vec lookat, float angle)
{
	t_camera		*camera;

	camera = (t_camera*)ft_malloc(sizeof(t_camera));
	camera->pos = pos;
	camera->lookat = lookat;
	camera->orientation = vec_normalize(vec_init(pos, lookat));//orientation a set correctement apres
	camera->top = get_top_vector(camera->orientation);
	camera->right = vec_opposite(vec_crossproduct(camera->orientation, camera->top));
	camera->fov = angle;
	camera->rotx = 0; // get l'angle de l'orientation;
	camera->roty = 0;
	camera->rotz = 0;
	camera->next = NULL;
	return (camera);
}

// manque la rotation en z de la cam, il faut son orientation (le vecteur) et sa rotation sur ce vecteur

t_light				*light_malloc(t_vec pos, t_color color, float intensity)
{
	t_light			*light;

	light = (t_light*)ft_malloc(sizeof(t_light));
	light->pos = pos;
	light->color = color;
	light->intensity = intensity;
	light->next = NULL;
	return (light);
}

t_ray			ray_init(t_vec a, t_vec b)
{
	t_ray		c;

	ft_bzero(&c, sizeof(t_ray));
	c.origin = a;
	c.direction = vec_norm(b);
	c.length = INFINITY;
	return (c);
}
