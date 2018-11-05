/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:47:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 17:39:02 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_vector		*create_vector(t_vertex *dest, t_vertex *origin)
{
	t_vector	*new;

	if (dest == NULL)
	{
		printf("dest must exist");
		return (NULL);
	}
	if (!(new = ft_memalloc(sizeof(t_vector))))
		return (NULL);
	new = init_vector(new, dest, origin);
	return (new);
}
