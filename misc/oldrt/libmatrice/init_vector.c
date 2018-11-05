/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:36:41 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 22:35:55 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_vector	*init_vector(t_vector *vec,t_vertex *dest, t_vertex *origin)
{
	if (origin == NULL)
		origin = &null_vertex;
	vec->x = dest->x - origin->x;
	vec->y = dest->y - origin->y;
	vec->z = dest->z - origin->z;
	vec->w = 0.0;
	vec->d = dest;
	vec->o = origin;

	return (vec);
}
