/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_struct_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 19:05:53 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.parser.h"

t_elem		create_elem()
{
	t_elem		new;

	new.main = 0;
	new.closed = 0;
	new.key = NULL;
	new.value = NULL;
	new.next = NULL;
	return new;
}


