/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:37:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/04 18:22:30 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_key		*init_sphere()
{
	t_key	*sphere;
	t_key	*child;

	sphere = new_key("sphere", ARRAY, false, NULL);
	//sphere->defaulty.objecty = default_vector_objects("position");
	sphere->child = basic_object_keys("position");
	return (sphere);
}

t_key		*init_objects()
{
	t_key	*begin;
	t_key	*obj;

	obj = new_key("objects", OBJECT, false, NULL);
	begin = obj;
	obj->child = init_sphere();
	obj = obj->child;
	
	return (begin);
}

t_key		*init_first_level_keys()
{
	t_key		*begin;
	t_key		*keys;

	keys = new_key(NULL, OBJECT, false, NULL);
	begin = keys;
	keys->child = new_key("name", STRING, true, NULL);
	//show_one_key(keys->child, 10);
	keys = keys->child;
	keys->next = init_objects();
	return (begin);
}

t_key			*first_level_keys()
{
	t_key		*first_level_keys;

	first_level_keys = init_first_level_keys();
	return (first_level_keys);
}


t_env		*rtv1_parsing(t_elem *begin, t_env *env)
{
	t_key	*key;

	printf("RTV1 PARSING\n");
	if (begin->type == ARRAY && begin->value.arrayi != NULL)
	{
		key = first_level_keys();
		print_keys(key, 0);
	}
	return (env);
}
