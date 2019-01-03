/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:23:44 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 21:48:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					init_camera(t_elem *elem, t_obj *obj)
{
	obj->params.camera.fov =
		default_float(
				required_float(
					parse_float(
						find_elem_by_key(elem, "fov")),
					FOV_REQUIRED,
					"fov"),
				20.0);
	if (obj->params.camera.fov <= 0 || obj->params.camera.fov >= 180)
		ft_error(FOV_BAD_FORMAT);
	obj->params.camera.fov = parse_degree_to_rad(obj->params.camera.fov);
	obj->type = CAMERA;
}

static inline void		camera_chained_array(t_obj **begin, t_obj **curr, t_obj **previous)
{
	if ((*begin) == NULL)
		(*begin) = (*curr);
	else if ((*previous) != NULL)
		(*previous)->next = (*curr);
	if ((*curr) != NULL)
		(*previous) = (*curr);
}

t_obj					*parse_cameras(t_elem *elem)
{
	t_obj		*begin;
	t_obj		*curr;
	t_obj		*previous;
	t_elem		*child_elem;

	begin = NULL;
	previous = NULL;
	if (elem != NULL)
	{
		child_elem = elem->value.arrayi;
		if (child_elem == NULL && CAMERAS_REQUIRED)
			is_required(elem->key, 1);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, &init_camera);
			camera_chained_array(&begin, &curr, &previous);
			child_elem = child_elem->next;
		}
	}
	else if (CAMERAS_REQUIRED)
		is_required("cameras", 0);
	return (begin);
}
