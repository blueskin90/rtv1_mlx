/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_singleton.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:21:42 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:22:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_ray		**renderer_getptr(void)
{
	static t_ray	*ptr = NULL;

	return (&ptr);
}

t_ray				*renderer_getray(int nb)
{
	return (*(renderer_getptr()) + nb);
}

t_ray				*renderer_get()
{
	return (*(renderer_getptr()));
}

int					renderer_getraymax(void)
{
	return (camera_get()->params.camera.raynumber);
}

static t_ray		*renderer_get_fromcamera(void)
{
	return (camera_get()->params.camera.rays);
}

void				renderer_set(void)
{
	t_ray			**ptr;

	ptr = renderer_getptr();
	if (ptr == NULL)
		printf("renderer_set has a renderer_getptr == null\n");
	*ptr = renderer_get_fromcamera();
}
