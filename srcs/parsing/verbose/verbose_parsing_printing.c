/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_parsing_printing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 05:58:45 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 06:01:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_object_common(t_obj *obj)
{
	printf("\t\t%-10s : ", "pos");
	print_vec(obj->pos);
	printf("\t\t%-10s : ", "right");
	print_vec(obj->right);
	printf("\t\t%-10s : ", "up");
	print_vec(obj->up);
	printf("\t\t%-10s : ", "dir");
	print_vec(obj->dir);
	print_color(obj->color, "color");
	print_color(obj->specular, "specular");
	print_color(obj->diffuse, "diffuse");
	printf("\t\t%-10s : \n", "world to obj");
	print_matrix(obj->world_to_obj);
	printf("\t\t%-10s : \n", "obj to world ");
	print_matrix(obj->obj_to_world);
}

void				print_object_specs(t_obj *obj)
{
	if (obj->type == CONE)
		ft_printf("\t\t%-10s : %f\n", "angle", obj->params.cone.angle);
	else if (obj->type == CYLINDER)
		ft_printf("\t\t%-10s : %f\n", "radius", obj->params.cylinder.radius);
	else if (obj->type == SPHERE)
		ft_printf("\t\t%-10s : %f\n", "radius", obj->params.sphere.radius);
	else if (obj->type == LIGHT)
		ft_printf("\t\t%-10s : %f\n", "intensity", obj->params.light.intensity);
	else if (obj->type == CAMERA)
		ft_printf("\t\t%-10s : %f\n", "fov", obj->params.camera.fov);
}

void				print_object(t_obj *obj)
{
	print_object_common(obj);
	print_object_specs(obj);
}
void				print_scene(t_scene *scene)
{
	ft_printf("\tname : %s\n", scene->name);
	print_objects(scene->objs);
	print_lights(scene->lights);
	print_cameras(scene->cameras);
}
