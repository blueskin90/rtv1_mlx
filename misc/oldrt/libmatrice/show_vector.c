/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:51:12 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 21:53:55 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

void		show_vector(t_vector *vec)
{
	dprintf(1,"vector : ");
	dprintf(1,"x : %5f y : %5f z : %5f w : %5f \n", vec->x, vec->y, vec->z, vec->w);
	dprintf(1,"origin : ");
	show_vertex(vec->o);
	dprintf(1,"\ndest : ");
	show_vertex(vec->d);
	dprintf(1,"\n");
}
