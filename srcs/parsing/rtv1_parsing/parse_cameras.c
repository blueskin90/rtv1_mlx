/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:23:44 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/18 16:55:23 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			init_camera(t_elem *elem, t_obj *obj)
{

	obj->params.camera.fov = 
		default_float(
				required_float(
					parse_degree_to_rad(
						parse_float(
							find_elem_by_key(elem, "fov")
							)
						),
					FOV_REQUIRED,
					"fov"	
					),
				0.0
				);	
	// TODO fov must be between ]0 et 180[
	obj->type = CAMERA;
//	obj->params.camera.rays = NULL;
//	obj->params.camera.raynumber = 0;

}

t_obj			*parse_cameras(t_elem *elem)
{
	t_obj		*begin;
	t_obj		*curr;
	t_obj		*previous;
	t_elem		*child_elem;

	begin = NULL;
	previous = NULL;
	if (elem != NULL) 
	{
		printf("PARSE CAMERAS\n");
		child_elem = elem->value.arrayi;
		if (child_elem == NULL && CAMERAS_REQUIRED)
			is_required(elem->key, true);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, &init_camera);
			if (begin == NULL)
				begin = curr;
			else if (previous != NULL)
				previous->next = curr;
			if (curr != NULL)
				previous = curr;
			child_elem = child_elem->next;
		}
	}
	else if (CAMERAS_REQUIRED)
		is_required("cameras", false);
	return (begin);

}
