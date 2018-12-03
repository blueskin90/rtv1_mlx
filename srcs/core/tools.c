/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:16:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 09:14:35 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float				maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float				minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int					clampi(int a, int inf_limit, int sup_limit)
{
	if (a < inf_limit)
		return (inf_limit);
	if (a > sup_limit)
		return (sup_limit);
	return (a);	
}

float					clampf(float a, float inf_limit, float sup_limit)
{
	if (a < inf_limit)
		return (inf_limit);
	if (a > sup_limit)
		return (sup_limit);
	return (a);	
}

void				*ft_malloc(size_t size)
{
	void			*ptr;

	if (!(ptr = malloc(size)))
		ft_error(MALLOC_FAIL);
	ft_bzero(ptr, size);
	return (ptr);
}

void				ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
