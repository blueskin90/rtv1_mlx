/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:58:29 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 22:37:56 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

void	normalize_vector(t_vector *vec)
{
	double magnitude;

	magnitude = magnitude_vector(vec);
	vec->x = vec->x / magnitude;
	vec->y = vec->y / magnitude;
	vec->z = vec->z / magnitude;
}
