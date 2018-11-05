/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalarproduct_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:12:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/18 15:12:58 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libmatrice.h"

t_vector	*scalarproduct_vector(t_vector *vec1, double sc)
{
	vec1->x = vec1->x * sc;
	vec1->y = vec1->y * sc;
	vec1->z = vec1->z * sc;
	return (vec1);
}
