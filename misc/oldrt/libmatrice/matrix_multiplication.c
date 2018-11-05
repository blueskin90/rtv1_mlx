/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:57:34 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/16 17:58:26 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

void			matrix_multiplication(t_matrix *t, t_vertex *point)
{
	double x;
	double y;
	double z;
	double w;
	
	x = (double)(point->x * t->x[0] + point->y * t->x[1] + point->z * t->x[2] + point->w * t->x[3]);
	y = (double)(point->x * t->y[0] + point->y * t->y[1] + point->z * t->y[2] + point->w * t->y[3]);
	z = (double)(point->x * t->z[0] + point->y * t->z[1] + point->z * t->z[2] + point->w * t->z[3]);
	w = (double)(point->x * t->w[0] + point->y * t->w[1] + point->z * t->w[2] + point->w * t->w[3]);

	point->x = x;
	point->y = y;
	point->z = z;
	point->w = w;
}

