/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mode_singleton.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:22:26 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:22:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int					*print_mode_getptr(void)
{
	static int		mode = 0;
	return (&mode);
}

int					print_mode_get(void)
{
	return (*(print_mode_getptr()));
}

void				print_mode_set(int mode)
{
	*(print_mode_getptr()) = mode;
}
