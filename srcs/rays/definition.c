/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:17:32 by toliver           #+#    #+#             */
/*   Updated: 2018/10/15 04:25:21 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

t_ray			ray_init(t_vertex a, t_vector b)
{
	t_ray		c;

	c.origin = a;
	c.dir = b;
	return (c);
}
