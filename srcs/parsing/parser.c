/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:37:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/27 22:08:03 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_key		create_key_on_stack(char *name, e_type type, bool required)
{
	return ((t_key){.name = name, .type = type, .required = required });
}

t_key		init_first_level_keys()
{
	t_key		keys;

	keys = create_key_on_stack("name", STRING, true);

}

int			first_level_keys(t_elem *first_level_elem)
{
	t_key		first_level_keys;
	init_first_level_keys();
}


t_env		*rtv1_parsing(t_elem *begin, t_env *env)
{

	if (begin->type == ARRAY && begin->value.arrayi != NULL)
	{
		

	}
}
