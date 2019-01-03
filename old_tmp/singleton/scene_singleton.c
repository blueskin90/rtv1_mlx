/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_singleton.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:20:54 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:21:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_scene		**scene_getptr(void)
{
	static t_scene	*ptr = NULL;
	return (&ptr);
}

t_scene				*scene_get(void)
{
	return (*(scene_getptr()));
}

void				scene_set(t_scene *scene)
{
	t_scene			**ptr;

	ptr = scene_getptr();
	if (ptr == NULL)
		printf("scene_set has a scene_getptr == null\n");
	*ptr = scene;
}
