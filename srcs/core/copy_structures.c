/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:58:50 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 03:29:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** ON NE SE SERT PLUS DE RIEN ICI, CONSERVER OCAZOU
*/

int					light_copy(t_env *env)
{
	t_light			*ptr;
	t_light			*cpyptr;

	ptr = env->scene->light;
	if (ptr)
	{
		env->scene_copy->light = light_malloc(ptr->pos, ptr->color, ptr->intensity);
		cpyptr = env->scene_copy->light;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = light_malloc(ptr->pos, ptr->color, ptr->intensity);
			cpyptr = cpyptr->next;
			ptr = ptr->next;
		}
	}
	return (1);
}

int					sphere_copy(t_env *env)
{
	t_obj			*ptr;
	t_obj			*cpyptr;

	ptr = env->scene->objs;
	if (ptr)
	{
		env->scene_copy->objs = ft_malloc(sizeof(t_obj));
		ft_memcpy(env->scene_copy->objs, ptr, sizeof(t_obj));
		cpyptr = env->scene_copy->objs;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = ft_malloc(sizeof(t_obj));
			ft_memcpy(cpyptr->next, ptr, sizeof(t_obj));
			cpyptr = cpyptr->next;
			ptr = ptr->next;
		}
	}
	return (1);
}

int					scene_copy(t_env *env)
{
	env->scene_copy = (t_scene*)ft_malloc(sizeof(t_scene));
	sphere_copy(env);
	light_copy(env);
	return (1);
}
