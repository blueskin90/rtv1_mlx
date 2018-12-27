/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_parsing_loops.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 05:56:24 by toliver           #+#    #+#             */
/*   Updated: 2018/12/27 03:06:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char				*object_type_string(t_obj *obj)
{
	if (obj->type == PLANE)
		return ("PLAN");
	if (obj->type == CONE)
		return ("CONE");
	if (obj->type == CYLINDER)
		return ("CYLINDER");
	if (obj->type == SPHERE)
		return ("SPHERE");
	if (obj->type == LIGHT)
		return ("LIGHT");
	if (obj->type == CAMERA)
		return ("CAMERA");
	return ("WRONG TYPE !");
}

void				print_scenes(t_scene *scene)
{
	t_scene			*ptr;
	int				scene_nbr;
	int				i;

	scene_nbr = 0;
	ptr = scene;
	while (ptr)
	{
		scene_nbr++;
		ptr = ptr->next;
	}
	i = 0;
	if (!(ptr = scene))
	{
		printf("\tNo scenes availlable\n");
		return ;
	}
	while (ptr)
	{
		i++;
		ft_printf(" ===== printing scene [%d] of [%d] =====\n\n", i, scene_nbr);
		print_scene(ptr);
		ptr = ptr->next;
		ft_printf("\n == end of printing scene [%d] of [%d] ==\n\n",
				i, scene_nbr);
	}
}

void					print_cameras(t_obj *cameras)
{
	t_obj				*ptr;
	int					cameras_nbr;
	int					i;

	ptr = cameras;
	cameras_nbr = 0;
	while (ptr)
	{
		cameras_nbr++;
		ptr = ptr->next;
	}
	i = 0;
	ptr = cameras;
	printf("\t&& printing cameras &&\n");
	while (ptr)
	{
		i++;
		ft_printf("\t- camera [%d] of [%d]\n", i, cameras_nbr);
		print_object(ptr);
		printf("\n");
		ptr = ptr->next;
	}
	printf("\t&& end of printing cameras &&\n");
}

void					print_lights(t_obj *lights)
{
	t_obj				*ptr;
	int					light_nbr;
	int					i;

	ptr = lights;
	light_nbr = 0;
	while (ptr)
	{
		light_nbr++;
		ptr = ptr->next;
	}
	i = 0;
	ptr = lights;
	printf("\t!! printing lights !!\n");
	while (ptr)
	{
		i++;
		ft_printf("\t- light [%d] of [%d]\n", i, light_nbr);
		print_object(ptr);
		printf("\n");
		ptr = ptr->next;
	}
	printf("\t!! end of printing lights !!\n");
}

void				print_objects(t_obj *obj)
{
	t_obj			*ptr;
	int				obj_nbr;
	int				i;

	ptr = obj;
	obj_nbr = 0;
	while (ptr)
	{
		obj_nbr++;
		ptr = ptr->next;
	}
	i = 0;
	ptr = obj;
	printf("\t## printing objects ##\n");
	while (ptr)
	{
		i++;
		ft_printf("\t- obj [%d] of [%d]\n", i, obj_nbr);
		ft_printf("\t\tIs a %s\n", object_type_string(obj));
		print_object(ptr);
		printf("\n");
		ptr = ptr->next;
	}
	printf("\t## end of printing objects ##\n");
}
