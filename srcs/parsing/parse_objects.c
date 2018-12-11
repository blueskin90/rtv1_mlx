/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 16:11:35 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


t_obj	*new_obj()
{
	t_obj		*obj;

	obj = (t_obj*)ft_malloc(sizeof(t_obj));
	return (obj);
}

t_obj	*parse_object(t_elem *elem, bool obj_req,
		t_obj *(*object_parser)(t_elem*, t_obj*), char *key)
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
		if (child_elem == NULL && obj_req)
			is_required(key, true);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, object_parser);
			if (begin == NULL)
				begin = curr;
			else if (previous != NULL)
				previous->next = curr;
			if (curr != NULL)
				previous = curr;
			child_elem = child_elem->next;
		}
	}
	else if (obj_req)
			is_required(key, false);
	return (begin);
}

t_obj		*add_objects_to_list(t_obj *current, t_obj *begin)
{
	t_obj		*tmp;

	if (current && begin == NULL)
		return current;
	else if (current == NULL && begin)
		return begin;
	else if (current && begin)
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
		return begin;
	}
	return begin;

}

t_obj		*parse_objects(t_elem *elem)
{
	t_obj		*obj;
	t_obj		*curr;
	t_obj		*prev;
	t_elem		*child_elem;

	obj = NULL;
	prev = NULL;
	curr = NULL;
	if (elem != NULL)
	{
		// y a un while ici 
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "spheres"), SPHERES_REQUIRED,
				&init_sphere, "spheres"), obj); 
		obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "planes"), PLANES_REQUIRED,
				&init_plane, "planes"), obj); 
		obj = add_objects_to_list(curr = parse_object(
				find_elem_by_key(child_elem, "cones"), CONES_REQUIRED,
				&init_cone, "cones"), obj); 
		obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "cylinders"), CYLINDERS_REQUIRED,
				&init_cylinder, "cylinders"), obj); 
		if (OBJECTS_REQUIRED && obj == NULL)
			is_required("object", true);
	}
	else if (OBJECTS_REQUIRED)
		ft_error(OBJECTS_IS_REQUIRED);
	else
		obj = NULL;
	return (obj);
}
