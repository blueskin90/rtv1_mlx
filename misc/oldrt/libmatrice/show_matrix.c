/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:16:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/16 20:25:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

static void		loop_true_line(double *line)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		printf(" %5f ", line[i]);
		printf(" | ");
		i++;
	}
	printf("\n");
}

void			show_matrix(t_matrix *t)
{
	loop_true_line(t->x);
	loop_true_line(t->y);
	loop_true_line(t->z);
	loop_true_line(t->w);
}
