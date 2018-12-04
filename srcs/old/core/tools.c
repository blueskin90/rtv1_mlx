/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:16:49 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 18:21:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				*ft_malloc(unsigned int size)
{
	void			*ptr;

	if (!(ptr = malloc(size)))
		ft_error(MALLOC_FAIL);
	return (ptr);
}

void				ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(0);
}
