/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:37:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/28 19:46:38 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_key		*init_sphere()
{
	t_key	*sphere;
	t_key	*child;

	sphere = new_key("sphere", ARRAY, false, NULL);
	//sphere->defaulty.objecty = default_vector_objects("position");
	sphere->child_key = basic_object_keys("position");
	return (sphere);
}

t_key		*init_objects()
{
	t_key	*begin;
	t_key	*obj;

	obj = new_key("objects", OBJECT, false, NULL);
	begin = obj;
	obj->child_key = init_sphere();
	obj = obj->child_key;
	
	return (begin);
}

t_key		*init_first_level_keys()
{
	t_key		*begin;
	t_key		*keys;

	keys = new_key(NULL, OBJECT, false, NULL);
	begin = keys;
	keys->child_key = new_key("name", STRING, true, NULL);
	keys = keys->child_key;
	keys->next = init_objects();
	return (begin);
}

int			first_level_keys()
{
	t_key		*first_level_keys;

	first_level_keys = init_first_level_keys();
	print_keys(first_level_keys, 0);
	return (0);
}


t_env		*rtv1_parsing(t_elem *begin, t_env *env)
{

	printf("RTV1 PARSING\n");
	if (begin->type == ARRAY && begin->value.arrayi != NULL)
	{
		first_level_keys();
	}
	return (env);
}
