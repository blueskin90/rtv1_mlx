/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rotation_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 17:45:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/16 18:11:26 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_matrix	*init_x_rotation(double x_angle, t_matrix *t)
{
	t->x[0] = 1;
	t->x[1] = 0;
	t->x[2] = 0;
	t->x[3] = 0;
	t->y[0] = 0;
	t->y[1] = cos(x_angle);
	t->y[2] = -sin(x_angle);
	t->y[3] = 0;
	t->z[0] = 0;
	t->z[1] = sin(x_angle);
	t->z[2] = cos(x_angle);
	t->z[3] = 0;
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = 0;
	t->w[3] = 1;
	return (t);
}

t_matrix	*init_y_rotation(double y_angle, t_matrix *t)
{
	t->x[0] = cos(y_angle);
	t->x[1] = 0;
	t->x[2] = sin(y_angle);
	t->x[3] = 0;
	t->y[0] = 0;
	t->y[1] = 1;
	t->y[2] = 0;
	t->y[3] = 0;
	t->z[0] = -sin(y_angle);
	t->z[1] = 0;
	t->z[2] = cos(y_angle);
	t->z[3] = 0;
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = 0;
	t->w[3] = 1;
	return (t);
}

t_matrix	*init_z_rotation(double z_angle, t_matrix *t)
{
	t->x[0] = cos(z_angle);
	t->x[1] = -sin(z_angle);
	t->x[2] = 0;
	t->x[3] = 0;
	t->y[0] = sin(z_angle);
	t->y[1] = cos(z_angle);
	t->y[2] = 0;
	t->y[3] = 0;
	t->z[0] = 0;
	t->z[1] = 0;
	t->z[2] = 1;
	t->z[3] = 0;
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = 0;
	t->w[3] = 1;
	return (t);
}

