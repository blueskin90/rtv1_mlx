/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:21:07 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 20:03:01 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				obj_add(t_scene *scene, t_obj *obj)
{
	t_obj			*ptr;

	ptr = scene->objs;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = obj;
	}
	else
		scene->objs = obj;
}

void				light_add(t_scene *scene, t_obj *light)
{
	t_obj			*ptr;

	ptr = scene->lights;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = light;
	}
	else
		scene->lights = light;
}

void				camera_add(t_scene *scene, t_obj *camera)
{
	t_obj			*ptr;

	ptr = scene->cameras;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = camera;
	}
	else
		scene->cameras = camera;
}

t_scene				*tmp_parsing(void)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			lookat;
	t_rgb			color;
	t_obj			*objptr;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	scene->next = NULL;

// SPHERES

	pos = vec_init0(-35, 30, -30);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0xa610ff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 4);
	obj_add(scene, objptr);

	pos = vec_init0(5, 0, 20);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0xffaaaa);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 4);
	obj_add(scene, objptr);

	pos = vec_init0(25, 12, -12);
	lookat = vec_init0(0, 0, 6);
	color = rgb_init(0x10ff10);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 4);
	obj_add(scene, objptr);

	pos = vec_init0(6, 6, 3);
	color = rgb_init(0x901044);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 4);
	obj_add(scene, objptr);

	pos = vec_init0(-3, -3, -3);
	color = rgb_init(0x9010f0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 4);
	obj_add(scene, objptr);

	// CYLINDER

	lookat = vec_init0(6, 6, 6);
	pos = vec_init0(-3, -3, -3);
	color = rgb_init(0xaaffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 1);
	obj_add(scene, objptr);

	lookat = vec_init0(-20, 21, 50);
	pos = vec_init0(-20, 20, 50);
	color = rgb_init(0xaaff00);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 1);
	obj_add(scene, objptr);

	lookat = vec_init0(-8, 19, 10);
	pos = vec_init0(-10, 20, 10);
	color = rgb_init(0xAA50FF);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 5);
	obj_add(scene, objptr);

	// CONE
	pos = vec_init0(-29, -40, 10);
	lookat = vec_init0(-30, -38, 11);
	color = rgb_init(0xaabbcc);
	color = rgb_init(0xff50aa);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cone_params(objptr, 30);
	obj_add(scene, objptr);
	// PLANE
	
	color = rgb_init(0xaabbcc);
	pos = vec_init0(0, -50, 0);
	lookat = vec_init0(0, -49, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	pos = vec_init0(0, 50, 0);
	lookat = vec_init0(0, 49, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	pos = vec_init0(50, 0, 0);
	lookat = vec_init0(49, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	pos = vec_init0(-50, 0, 0);
	lookat = vec_init0(-49, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = rgb_init(0xaabbcc);
	pos = vec_init0(0, 0, 50);
	lookat = vec_init0(0, 0, 49);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	/*
	color = rgb_init(0xaabbcc);
	pos = vec_init0(0, 0, -50);
	lookat = vec_init0(0, 0, -49);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);
	*/

/*
	pos = vec_init0(15, 25, -15);
	color = rgb_init(0xFFFFFF);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 1);
	obj_add(scene, objptr);

	pos = vec_init0(-15, 25, -15);
	color = rgb_init(0xFFFFFF);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 1);
	obj_add(scene, objptr);
	*/
// 2 lights

//	lookat = vec_init0(0, -3, 1);
	pos = vec_init0(15, 25, -15);
	color = rgb_init(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.6);
	light_add(scene, objptr);

	pos = vec_init0(-15, 25, -15);
	color = rgb_init(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.9);
	light_add(scene, objptr);
// 1 camera

	pos = vec_init0(0, 25, -200);
	lookat = vec_init0(0, -50, 50);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	
	obj_camera_params(objptr, 60.0);
	camera_add(scene, objptr);

	scene->name = "test_de_base";
	return (scene);
}

