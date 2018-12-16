/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:50:43 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/28 17:13:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


t_key		*new_key(char *name, e_type type, bool required, void *defaulty)
{
	t_key		*new;

	new = ft_malloc(sizeof(t_key));
	new->name = name;
	new->type = type;
	new->required = required;
	new->defaulty = set_value_of_type(type, defaulty);
	return (new);
}
