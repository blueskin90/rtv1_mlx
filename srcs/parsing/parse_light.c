/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:56:25 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 18:36:03 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_obj		*parse_light(t_elem *elem)
{
	t_obj	*obj;
	t_elem	*child_elem;

	check_type_of_key("light", elem->type);
	// verifier que le type soit bien un objet
	obj = new_obj();
	child_elem = elem->value.arrayi;
	obj->pos = parse_vector(
			find_elem_by_key(child_elem, "position"));
	obj->dir = parse_vector(
			find_elem_by_key(child_elem, "orientation"));
	return (obj);
}

t_obj				*parse_lights(t_elem *elem)
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
		if (child_elem == NULL && LIGHTS_REQUIRED)
			is_required(elem->key, true);
		while (child_elem)
		{
			curr = parse_light(child_elem);
			if (begin == NULL)
				begin = curr;
			else if (previous != NULL)
				previous->next = curr;
			if (curr != NULL)
				previous = curr;
			child_elem = child_elem->next;
		}
	}
	else if (LIGHTS_REQUIRED)
			is_required("lights", false);
	return (begin);

}
