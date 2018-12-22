/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:16:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/22 18:26:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

void				ft_illegal_flag(char flag)
{
	ft_putstr_fd("rtv1: illegal option -- %c\n", flag);
}
