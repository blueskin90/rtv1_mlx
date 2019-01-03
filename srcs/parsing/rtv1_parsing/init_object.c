/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 12:08:23 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 21:01:15 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_cone(t_elem *elem, t_obj *obj)
{
	obj->type = CONE;
	obj->params.cone.angle =
		default_float(
			required_float(
				parse_degree_to_rad(
					parse_float(
						find_elem_by_key(elem, "angle"))),
				CONE_ANGLE_REQUIRED,
				"Angle of plane"),
			0.0);
	obj->intersect = &cone_intersection;
}

void		init_plane(t_elem *elem, t_obj *obj)
{
	(void)elem;
	(void)obj;
	obj->type = PLANE;
	obj->intersect = &plane_intersection;
}

void		init_cylinder(t_elem *elem, t_obj *obj)
{
	obj->type = CYLINDER;
	obj->params.cylinder.radius =
		default_float(
			required_float(
				parse_radius(
					parse_float(
						find_elem_by_key(elem, "radius"))),
				CYLINDER_RADIUS_REQUIRED,
				"Radius of cylinder"),
			0.0);
	obj->intersect = &cylinder_intersection;
}

void		init_sphere(t_elem *elem, t_obj *obj)
{
	obj->type = SPHERE;
	obj->params.sphere.radius =
		default_float(
			required_float(
				parse_radius(
					parse_float(
						find_elem_by_key(elem, "radius"))),
				SPHERE_RADIUS_REQUIRED,
				"Radius of sphere"),
			0.0);
	obj->intersect = &sphere_intersection;
}
