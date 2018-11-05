/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:14:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/16 20:13:09 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_matrix	*create_matrix(void)
{
	t_matrix	*new;

	if (!(new = ft_memalloc(sizeof(t_matrix))))
		return (NULL);
	ft_bzero(new->x,sizeof(double) * 4);
	ft_bzero(new->y, sizeof(double) * 4);
	ft_bzero(new->z, sizeof(double) * 4);
	ft_bzero(new->w, sizeof(double) * 4);
	return (new);
}
