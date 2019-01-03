/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arithmetic_values.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:18:34 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 21:11:48 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		parse_degree_to_rad(float angle)
{
	if (angle == INFINITY)
		return (INFINITY);
	angle = fmod(angle, 360);
	// TODO angle peut etre negatif ?
	return (degtorad(angle));
}

float		parse_radius(float radius)
{
	if (radius == INFINITY)
		return (INFINITY);
	if (radius <= 0)
		ft_error(RADIUS_BAD_FORMAT);
	return (radius);
}

float		parse_float(t_elem *elem)
{
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		if (elem->type == INTEGER)
			return ((float)elem->value.inty);
		return (elem->value.floaty);
	}
	else if (VECTOR_POINT_REQUIRED)
		ft_error(VECTOR_POINT_IS_REQUIRED);
	return (INFINITY);
}
