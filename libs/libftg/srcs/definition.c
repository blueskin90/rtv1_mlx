/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:17:32 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 17:58:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vertex		vertex_init(float x, float y, float z)
{
	t_vertex	a;

	a.x = x;
	a.y = y;
	a.z = z;
	a.w = 1;
	return (a);
}

t_vector		vector_init(t_vertex a, t_vertex b)
{
	t_vector	c;

	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	c.w = 0;
	return (c);
}
