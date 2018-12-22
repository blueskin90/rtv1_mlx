/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps_singleton.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 00:17:37 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 00:26:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int			*step_getptr(void)
{
	static	int		step = 0;

	return (&step);
}

int					step_get(void)
{
	return (*(step_getptr()));
}

void				step_set(int value)
{
	int				*ptr;

	ptr = step_getptr();
	if (ptr == NULL)
		printf("step_set has an int ptr == NULL\n");
	*ptr = value;
} // voir pour mettre un next ou autre
