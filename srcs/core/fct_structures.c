/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_structures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:01:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/09 19:02:10 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_sphere			*sphere_malloc(t_vertex p, float rad, t_vector r, t_color c)
{
	t_sphere		*sphere;

	sphere = (t_sphere*)ft_malloc(sizeof(t_sphere));
	sphere->pos = p;
	sphere->radius = rad;
	sphere->orientation = r;
	sphere->color = c;
	sphere->next = NULL;
	return (sphere);
}

t_camera			*camera_malloc(t_vertex pos, t_vector orientation)
{
	t_camera		*camera;

	camera = (t_camera*)ft_malloc(sizeof(t_camera));
	camera->pos = pos;
	camera->orientation = orientation;
	camera->next = NULL;
	return (camera);
}

// manque la rotation en z de la cam, il faut son orientation (le vecteur) et sa rotation sur ce vecteur

t_light				*light_malloc(t_vertex pos, t_color color)
{
	t_light			*light;

	light = (t_light*)ft_malloc(sizeof(t_light));
	light->pos = pos;
	light->color = color;
	light->next = NULL;
	return (light);
}
