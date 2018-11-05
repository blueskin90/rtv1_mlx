/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_vertex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:35:12 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 17:42:02 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_vertex		*create_vertex(int x, int y, int z)
{
	t_vertex	*new;

	if (!(new = ft_memalloc(sizeof(t_vertex))))
		return (NULL);
	new = init_vertex(x, y, z, new);
	return (new);
}
