/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_singleton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:19:10 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:20:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_obj		**camera_getptr(void)
{
	static t_obj	*ptr = NULL;
	return (&ptr);
}

t_obj				*camera_get(void)
{
	return (*(camera_getptr()));
}

void				camera_set(t_obj *camera)
{
	t_obj			**ptr;

	ptr = camera_getptr();
	if (ptr == NULL)
		printf("camera_set has a camera_getptr == null\n");
	*ptr = camera;
}
