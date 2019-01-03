/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definition.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:17:32 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:02:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec		vec_init(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = b.x - a.x;
	c.y = b.y - a.y;
	c.z = b.z - a.z;
	c.w = 0;
	return (c);
}

t_vec		vec_init0(float x, float y, float z)
{
	t_vec	c;

	c.x = x;
	c.y = y;
	c.z = z;
	c.w = 0;
	return (c);
}
