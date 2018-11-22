/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:01:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 03:31:47 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	sphere->next = NULL;
	return (sphere);
}

t_obj			*cylinder_malloc(t_vec p, float rad, t_vec lookat, t_color c)
{
	t_obj		*cylinder;

	cylinder = (t_obj*)ft_malloc(sizeof(t_obj));
	cylinder->pos = p;
	cylinder->params.cylinder.radius = rad;
	cylinder->params.cylinder.axis = vec_normalize(vec_init(p, lookat));
	cylinder->rot = cylinder->params.cylinder.axis;
	cylinder->color = c;
	cylinder->type = CYLINDER;
	cylinder->intersect = &cylinder_intersection;
	cylinder->next = NULL;
	return (cylinder);
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
