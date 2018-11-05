/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:31:16 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 22:37:17 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vertex circle = {2,1,2};
int		scale = 2;


int		in_sphere(t_vector *vec)
{
	double	disc;
	double	b;
	double	c;
	double	t[2];

	normalize_vector(vec);
	b = 2 * (vec->x * (vec->o->x - circle.x)
			+ vec->y * (vec->o->y - circle.y)
			+ vec->z * (vec->o->z - circle.z));
	c = (vec->o->x - circle.x) * (vec->o->x - circle.x) +
		(vec->o->y - circle.y) * (vec->o->y - circle.y) +
		(vec->o->z - circle.z) * (vec->o->z - circle.z) - (scale * scale);
	disc = sqrt((b * b)*2 - 4*c);
	//dprintf(1, "b : %f c : %f disc : %f\n", b, c , disc);
	if (disc >= 0)
	{
		t[0] = (- b - disc) /2;
		t[1] = (- b + disc) /2;
		if (t[0] > 0)
			return (t[0]);
		else if (t[1] > 0)
			return (t[1]);
	}
	return (0);
}
