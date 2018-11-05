/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_projection_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:05:25 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/18 16:18:18 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_matrix	*init_projection(t_proj *p, t_matrix *t)
{
	double	s;
	
	s = 1.0 / (tan(ft_to_radians(p->fov) * 0.5));
	t->x[0] = s / p->ratio;
	t->x[1] = 0;
	t->x[2] = 0;
	t->x[3] = 0;
	t->y[0] = 0;
	t->y[1] = s;
	t->y[2] = 0;
	t->y[3] = 0;
	t->z[0] = 0;
	t->z[1] = 0;
	t->z[2] = -1 * (-p->near - p->far) / (p->near - p->far);
	t->z[3] = (2 * p->near * p->far) / (p->near - p->far);
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = -1;
	t->w[3] = 0;
	return (t);
}
