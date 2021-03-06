/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:42:24 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 18:09:04 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void			object_chain_array(t_obj **begin, t_obj **curr,
		t_obj **previous)
{
	if ((*begin) == NULL)
		(*begin) = (*curr);
	else if ((*previous) != NULL)
		(*previous)->next = (*curr);
	if ((*curr) != NULL)
		(*previous) = (*curr);
}

t_obj				*parse_object(t_elem *elem, int obj_req,
		void (*object_parser)(t_elem*, t_obj*), char *key)
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
			is_required(key, 1);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, object_parser);
			object_chain_array(&begin, &curr, &previous);
			child_elem = child_elem->next;
		}
	}
	else if (obj_req)
		is_required(key, 0);
	return (begin);
}

t_obj				*add_objects_to_list(t_obj *current, t_obj *begin)
{
	t_obj		*tmp;

	if (current && begin == NULL)
		return (current);
	else if (current == NULL && begin)
		return (begin);
	else if (current && begin)
	{
		tmp = begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
		return (begin);
	}
	return (begin);
}

static t_obj		*parse_all_object_types(t_elem *child_elem, t_obj *obj)
{
	obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "spheres"), SPHERES_REQUIRED,
				&init_sphere, "spheres"), obj);
	obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "planes"), PLANES_REQUIRED,
				&init_plane, "planes"), obj);
	obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "cones"), CONES_REQUIRED,
				&init_cone, "cones"), obj);
	obj = add_objects_to_list(parse_object(
				find_elem_by_key(child_elem, "cylinders"), CYLINDERS_REQUIRED,
				&init_cylinder, "cylinders"), obj);
	return (obj);
}

t_obj				*parse_objects(t_elem *elem)
{
	t_obj		*obj;
	t_elem		*child_elem;

	obj = NULL;
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		obj = parse_all_object_types(child_elem, obj);
		if (OBJECTS_REQUIRED && obj == NULL)
			is_required("object", 1);
	}
	else if (OBJECTS_REQUIRED)
		ft_error(OBJECTS_IS_REQUIRED);
	else
		obj = NULL;
	return (obj);
}
