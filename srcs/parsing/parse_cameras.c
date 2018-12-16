/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cameras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:23:44 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 19:00:29 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_obj	*parse_camera(t_elem *elem)
{
	t_obj	*obj;
	t_elem	*child_elem;

	check_type_of_key("camera", elem->type);
	// verifier que le type soit bien un objet
	obj = new_obj();
	child_elem = elem->value.arrayi;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "orientation"));
	return (obj);
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
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.arrayi;
		if (child_elem == NULL && CAMERAS_REQUIRED)
			is_required(elem->key, true);
		while (child_elem)
		{
			curr = parse_camera(child_elem);
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
