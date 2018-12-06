/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:40:03 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 18:53:06 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_obj	*new_obj()
{
		t_obj		*obj;

		obj = (t_obj*)ft_malloc(sizeof(t_obj));
		return (obj);
}
t_obj	*parse_one_sphere(t_elem *elem)
{
		t_obj	*obj;
		t_elem	*child_elem;

		if (!check_type_of_key(elem->key, elem->type))
			ft_error(SPHERE_BAD_FORMAT);
		// verifier que le type soit bien un objet
		obj = NULL;
		obj = new_obj();
		child_elem = elem->value.arrayi;
		obj->pos = parse_vector(
						find_elem_by_key(child_elem, "position"));
		obj->dir = parse_vector(
						find_elem_by_key(child_elem, "orientation"));
		return (obj);
		// si l objet est vide
}

t_obj	*parse_spheres(t_elem *elem)
{
		t_obj		*begin;
		t_obj		*curr;
		t_obj		*previous;
		t_elem		*child_elem;

		begin = NULL;
		previous = NULL;
		if (elem != NULL) 
		{
				if (!check_type_of_key(elem->key, elem->type))
						ft_error(SPHERES_BAD_FORMAT);
				child_elem = elem->value.arrayi;
				if (child_elem == NULL && ONE_SPHERE_REQUIRED)
						ft_error(ONE_SPHERE_IS_REQUIRED);
				while (child_elem)
				{
						curr = parse_one_sphere(child_elem);
						if (begin == NULL)
								begin = curr;
						else if (previous != NULL)
								previous->next = curr;
						if (curr != NULL)
								previous = curr;
						child_elem = child_elem->next;
				}
		}
		else if (SPHERES_REQUIRED)
				ft_error(SPHERES_IS_REQUIRED);
		return (begin);
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
				if (!check_type_of_key(elem->key, elem->type))
						ft_error(OBJECTS_BAD_FORMAT);
				child_elem = elem->value.objecty;
				curr = parse_spheres(find_elem_by_key(child_elem, "spheres")); 
				if (obj == NULL)
						obj = curr;
				else if (curr != NULL)
				{
						prev->next = curr;
						prev = curr;
				}
				elem = elem->next;
		}
		else if (OBJECTS_REQUIRED)
				ft_error(OBJECTS_IS_REQUIRED);
		else
				obj = NULL;
		return (obj);
}
