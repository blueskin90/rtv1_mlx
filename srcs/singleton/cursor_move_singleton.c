/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move_singleton.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:24:40 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:26:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int			*cursor_getptrx(void)
{
	static int		x = 0;
	return (&x);
}

static int			*cursor_getptry(void)
{
	static int		y = 0;
	return (&y);
}

int					cursor_getx(void)
{
	return (*(cursor_getptrx()));
}

int					cursor_gety(void)
{
	return (*(cursor_getptry()));
}

void				cursor_movex(int x)
{
	int				*xptr;

	xptr = cursor_getptrx();
	if (*xptr + x > win_getx())
		*xptr = *xptr + x - win_getx();
	else if (*xptr + x < 0)
		*xptr = *xptr + x + win_getx();
	else
		*xptr = *xptr + x;
}

void				cursor_movey(int y)
{
	int				*yptr;

	yptr = cursor_getptry();
	if (*yptr + y > win_gety())
		*yptr = *(yptr) + y - win_gety();
	else if (*yptr + y < 0)
		*yptr = *(yptr) + y + win_gety();
	else
		*yptr = *yptr + y;
}

void				cursor_reset(void)
{
	int				*ptr;

	ptr = cursor_getptrx();
	*ptr = 0;
	ptr = cursor_getptry();
	*ptr = 0;
}
