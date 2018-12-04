/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:38:48 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/28 18:39:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_elem		*default_vector_values()
{
	t_elem	*elem;
	t_elem	*begin;
	float	val;

	val = 0.0;
	elem = create_init_elem("x", FLOAT, &val);
	begin = elem;
	elem->next = create_init_elem("y", FLOAT, &val);
	elem = elem->next;
	elem->next = create_init_elem("z", FLOAT, &val);
	return (begin);
}

t_elem		*default_vector_object(char *name)
{
	t_elem	*begin;
	t_elem	*elem;
	float	val;

	val = 0.0;
	elem = create_init_elem(name, OBJECT, NULL);
	begin = elem;
	elem->value.objecty = default_vector_values();
	return (begin);
}
