/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:56:25 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 16:41:23 by cvermand         ###   ########.fr       */
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
						find_elem_by_key(elem, "intensity")),
					INTENSITY_REQUIRED,
					"intensity"),
				1.0);
	if (obj->params.light.intensity < 0 || obj->params.light.intensity > 1)
		ft_error(ITENSITITY_BAD_FORMAT);
}

void				light_chain_array(t_obj **begin, t_obj **curr,
		t_obj **previous)
{
	if ((*begin) == NULL)
		(*begin) = (*curr);
	else if ((*previous) != NULL)
		(*previous)->next = (*curr);
	if ((*curr) != NULL)
		(*previous) = (*curr);
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
		child_elem = elem->value.arrayi;
		if (child_elem == NULL && LIGHTS_REQUIRED)
			is_required(elem->key, 1);
		while (child_elem)
		{
			curr = parse_one_object(child_elem, &init_light);
			light_chain_array(&begin, &curr, &previous);
			child_elem = child_elem->next;
		}
	}
	else if (LIGHTS_REQUIRED)
		is_required("lights", 0);
	return (begin);
}
