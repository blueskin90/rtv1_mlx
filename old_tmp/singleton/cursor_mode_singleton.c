/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mode_singleton.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:23:40 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:24:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int			*cursor_mode_getptr(void)
{
	static int		mode = 0;
	return (&mode);
}

int					cursor_mode_get(void)
{
	return (*(cursor_mode_getptr()));
}

void				cursor_mode_toggle(void)
{
	*(cursor_mode_getptr()) = (cursor_mode_get() ^ 1);
}

void				cursor_mode_set(int value)
{
	*(cursor_mode_getptr()) = value % 2;
}
