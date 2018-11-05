/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_vectors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:07:16 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/18 15:13:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_vector	*sub_vectors(t_vector *vec1, t_vector *vec2)
{
	vec1->x = vec1->x - vec2->x;
	vec1->y = vec1->y - vec2->y;
	vec1->z = vec1->z - vec2->z;
	return (vec1);
}
