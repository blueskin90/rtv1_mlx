/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:45:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 14:13:39 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		default_float(float number, float def)
{
	if (number == INFINITY)
		return (def);
	return (number);
}

t_vec		default_vec(t_vec vec, t_vec def)
{
	if (vec.x == INFINITY)
		vec.x = def.x;
	else if (vec.y == INFINITY)
		vec.y = def.y;
	else if (vec.z == INFINITY)
		vec.z = def.z;
	return (vec);
}
