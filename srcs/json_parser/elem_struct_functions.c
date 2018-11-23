/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_struct_functions->c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:00:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 20:29:57 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "json_parser.h"

t_elem		*create_elem()
{
	t_elem		*new;
 
	new = ft_malloc(sizeof(t_elem));
	new->main = 0;
	new->closed = 0;
	new->key = NULL;
	new->value.inty = NULL;
	new->next = NULL;
	new->type = NOTYPE;
	return new;
}
