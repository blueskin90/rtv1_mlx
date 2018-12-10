/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:06:35 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 18:36:18 by cvermand         ###   ########.fr       */
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
		if (!check_type_of_key(elem->key, elem->type))
			ft_error(SCENE_NAME_BAD_FORMAT);
		// on accepte nom "" ? 
		return (ft_strdup(elem->value.stringy));
	}
	else if (NAME_REQUIRED)
		ft_error(NAME_IS_REQUIRED);
	// rajouter le numero de scene
	return (ft_strdup("NO NAME"));
}

t_scene				*parse_scene(t_elem *elem)
{
	t_scene		*scene;
	t_elem		*child;

	// .h avec les valeurs par defaut ?
	if (!check_type_of_key("scene",elem->type))
		ft_error(SCENE_BAD_FORMAT);
	child = elem->value.objecty;
	scene = new_scene();
	scene->name = 
		parse_scene_name(find_elem_by_key(child, "name"));
	scene->objs = parse_objects(find_elem_by_key(child, "objects"));
	scene->lights = parse_lights(find_elem_by_key(child, "lights"));
	scene->cameras = parse_cameras(find_elem_by_key(child, "cameras"));
	print_new_scene(scene);
	//scene->objs = parse_objects(elem);
	// name, objects, lights, camera
	// TODO condition finale style, au moins un object
	return (scene);
}
