/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 17:21:48 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 19:00:14 by cvermand         ###   ########.fr       */
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
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

