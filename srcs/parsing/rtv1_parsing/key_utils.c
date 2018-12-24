/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:21:48 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/17 21:10:35 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_elem		*find_elem_by_key(t_elem *elem, char *key)
{
	t_elem		*curr;

	curr = elem;
	while (curr)
	{
		if (curr->key != NULL && !ft_strcmp(curr->key, key))
		{
			check_type_of_key(key, curr->type);
			return (curr);
		}
		curr = curr->next;
	}
	return (NULL);
}

