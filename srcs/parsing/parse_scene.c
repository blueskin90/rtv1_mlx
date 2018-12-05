/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:06:35 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 17:53:03 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_scene		*new_scene()
{
	t_scene	*scene;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	ft_bzero((void *)scene, sizeof(t_scene));
	return (scene);
}

static	char		*parse_scene_name(t_elem *elem)
{
	if (elem != NULL)
	{
		// on accepte nom "" ? 
		if (elem->type == STRING)
		{
			return (ft_strdup(elem->value.stringy));
		}
		else
			ft_error(SCENE_NAME_BAD_FORMAT);
	}
	// rajouter le numero de scene
	return (ft_strdup("NO NAME"));
}

t_scene				*parse_scene(t_elem *elem, int nbr_scene)
{
	t_scene		*scene;

	scene = NULL;
	if (elem->type == OBJECT)
	{
		scene = new_scene();
		scene->name = parse_scene_name(find_elem_by_key(elem, "name"));
		print_new_scene(scene);
		//scene->objs = parse_objects(elem);
	}
	else
	{
		printf("WRONG SCENE FORMAT, MUST BE OBJECT");
		ft_error(SCENE_BAD_FORMAT);
	}
	// name, objects, lights, camera

	return (scene);
}
