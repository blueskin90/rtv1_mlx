/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_struct_functions->c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42->fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:00:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/27 17:22:50 by cvermand         ###   ########.fr       */
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
	//ft_bzero((void *)new->value);
	new->value.inty = 0;
	new->next = NULL;
	new->type = NOTYPE;
	return new;
}
