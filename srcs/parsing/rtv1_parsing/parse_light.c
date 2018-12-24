/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:56:25 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/18 16:54:48 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void				init_light(t_elem *elem, t_obj *obj)
{
	obj->type = LIGHT;
	obj->params.light.intensity = 
		default_float(
				required_float(
						parse_float(
								find_elem_by_key(elem, "intensity")
						),
					INTENSITY_REQUIRED,
					"intensity"
					),
				1.0
				);	
	// verifier que ca se situe entre 0 et 1 ! 
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
		printf("PARSE LIGHHHHHT\n");
//		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.arrayi;
		if (child_elem == NULL && LIGHTS_REQUIRED)
			is_required(elem->key, true);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, &init_light);
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
