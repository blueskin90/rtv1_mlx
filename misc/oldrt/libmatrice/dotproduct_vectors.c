/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotproduct_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:14:53 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/18 15:24:29 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

double		dotproduct_vectors(t_vector *vec1, t_vector *vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y +  vec1->z * vec2->z);
}
