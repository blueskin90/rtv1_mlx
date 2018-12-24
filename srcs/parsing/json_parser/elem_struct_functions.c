/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_struct_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 21:37:39 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:39:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

u_value		set_value_of_type(e_type type, void *value)
{
	u_value		val;

	if (type == INTEGER)
		val.inty = *((int*)value);
	if (type == FLOAT)
		val.floaty = *((float *)value);
	if (type == STRING)
		val.stringy = (char *)value;
	if (type == BOOL)
		val.booly = *((bool *)value);
	if (type == NULL_ELEM)
		val.nully = 0;
	if (type == ARRAY)
		val.arrayi = value;
	if (type == OBJECT)
		val.objecty = value;
	return (val);
}

t_elem		*create_init_elem(char *key, e_type type, void *value)
{
	t_elem		*new;

	new = json_malloc(sizeof(t_elem));
	new->main = 0;
	new->closed = 0;
	new->key = key;
	new->value = set_value_of_type(type, value);
	new->next = NULL;
	new->type = type;
	return (new);
}

t_elem		*create_elem(void)
{
	t_elem		*new;

	new = json_malloc(sizeof(t_elem));
	new->main = 0;
	new->closed = 0;
	new->key = NULL;
	new->value.inty = 0;
	new->next = NULL;
	new->type = NOTYPE;
	return (new);
}
