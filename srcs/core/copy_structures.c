/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:58:50 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/09 18:59:25 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					light_copy(t_env *env)
{
	t_light			*ptr;
	t_light			*cpyptr;

	ptr = env->scene->light;
	if (ptr)
	{
		env->scene_copy->light = light_malloc(ptr->pos, ptr->color);
		cpyptr = env->scene_copy->light;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = light_malloc(ptr->pos, ptr->color);
			cpyptr = cpyptr->next;
			ptr = ptr->next;
		}
	}
	return (1);
}
int					sphere_copy(t_env *env)
{
	t_sphere		*ptr;
	t_sphere		*cpyptr;

	ptr = env->scene->sphere;
	if (ptr)
	{
		env->scene_copy->sphere = sphere_malloc(ptr->pos, ptr->radius, ptr->orientation, ptr->color);
		cpyptr = env->scene_copy->sphere;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = sphere_malloc(ptr->pos, ptr->radius, ptr->orientation, ptr->color);
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
