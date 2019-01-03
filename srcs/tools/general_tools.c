/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:16:23 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 22:31:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*string_to_lower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
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

void				ft_illegal_flag(char flag)
{
	ft_putstr_fd("rtv1: illegal option -- %c\n", flag);
}
