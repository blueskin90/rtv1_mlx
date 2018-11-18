/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:01:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 18:09:13 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj			*plane_malloc(t_vec p, t_vec dir, t_vec normal, t_color c)
{
	t_obj		*plane;

	plane = (t_obj*)ft_malloc(sizeof(t_obj));
	plane->pos = p;
	plane->params.plane.normal = normal;
	plane->params.plane.normal_norm = vec_normalize(normal);
	plane->rot = dir;
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

t_camera			*camera_malloc(t_vec pos, t_vec lookat, float angle)
{
	t_camera		*camera;

	camera = (t_camera*)ft_malloc(sizeof(t_camera));
	camera->pos = pos;
	camera->lookat = lookat;
	camera->orientation = vec_normalize(lookat);//orientation a set correctement apres
	camera->top = vec_init0(0, 1, 0);
	camera->right = vec_init0(1, 0, 0);
	camera->fov = angle;
	camera->rotx = 0; // get l'angle de l'orientation;
	camera->roty = 0;
	camera->rotz = 0;
	camera->next = NULL;
	return (camera);
}

// manque la rotation en z de la cam, il faut son orientation (le vecteur) et sa rotation sur ce vecteur

t_light				*light_malloc(t_vec pos, t_color color)
{
	t_light			*light;

	light = (t_light*)ft_malloc(sizeof(t_light));
	light->pos = pos;
	light->color = color;
	light->next = NULL;
	return (light);
}

t_ray			ray_init(t_vec a, t_vec b)
{
	t_ray		c;

	c.origin = a;
	c.direction = b;
	ft_memset(&c.color, 0,sizeof(c.color));
	c.obj = 0;
	return (c);
}
