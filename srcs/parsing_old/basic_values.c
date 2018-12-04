/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:57:58 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/04 18:08:06 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_key		*basic_vector_keys()
{
	t_key	*begin;
	t_key	*key;
	float	val;

	val = 0.0;
	key = new_key("x", FLOAT, false, &val);
	begin = key;
	key->next = new_key("y", FLOAT, false, &val);
	key = key->next;
	key->next =new_key ("z", FLOAT, false, &val); 
	return (begin);
}

t_key		*basic_object_keys(char *name)
{
	t_key	*key;
	float	val;

	val = 0.0;
	key = new_key(name, OBJECT, false, NULL);
	key->defaulty.objecty = default_vector_values();
	key->child = basic_vector_keys();
	return (key);
}
