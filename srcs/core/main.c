/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 07:14:52 by toliver          ###   ########.fr       */
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

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			lookat;
	t_color			color;
	t_obj			*objptr;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));

	// 10 obj
	pos = vec_init0(-35, 30, -30);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0xa610ff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 5);
	obj_add(scene, objptr);
	
	pos = vec_init0(5, 0, 20);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0xffaaaa);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 5);
	obj_add(scene, objptr);


	pos = vec_init0(25, 12, -12);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0x10ff10);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 7);
	obj_add(scene, objptr);


	pos = vec_init0(-5, 5, 20);
	color = color_init_hsl(0x30ff30);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 1.0);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, -9, 0);
	pos = vec_init0(0, -10, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	lookat = vec_init0(6, 6, 6);
	pos = vec_init0(10, -2, -3);
	color = color_init_hsl(0xaaff00);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 1);
	obj_add(scene, objptr);
	
	pos = vec_init0(-10, 0, 20);
	color = color_init_hsl(0x8080ff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 2);
	obj_add(scene, objptr);


	pos = vec_init0(-10, 0, 20);
	lookat = vec_init0(-11, 1, 21);
	color = color_init_hsl(0xff5050);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cone_params(objptr, 22);
	obj_add(scene, objptr);
	
	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, 50, 0);
	pos = vec_init0(0, 51, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(49, 0, 0);
	pos = vec_init0(50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(-49, 0, 0);
	pos = vec_init0(-50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, 0, 50);
	pos = vec_init0(0, 0, 49);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

// 2 lights

	lookat = vec_init0(0, -3, 1);
	pos = vec_init0(15, 25, -15);
	color = color_init_hsl(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.6);
	light_add(scene, objptr);

	pos = vec_init0(-15, 25, -15);
	color = color_init_hsl(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.9);
	light_add(scene, objptr);

// 1 camera

	env->scene = scene;
	pos = vec_init0(0, 15, -100);
	lookat = vec_init0(0, 0, 5);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_camera_params(objptr, 60.0);
	camera_add(scene, objptr);
	return (1);
}

int					main(int ac, char **av)
{
	t_env			*env;

	env = env_init();
	env_set(env); // toujours init et set lenv avant tout;
	parse_scene(env); // puis parsing bidon
	scene_set(env->scene); // set la scene actuelle a la premiere
	camera_set(env->scene->cameras); // set la camera a la premiere;
	renderer_set(); // set le renderer a la camera actuelle;
	printf("settings done\n");
	raytracing();
	printf("raytracing first pass done\n");
	raytracing_lights();
	printf("raytracing lights pass done\n");
	printing();
	printf("printing done\n");
	events_listener(env);
	mlx_loop(mlx_get());
	(void)ac;
	(void)av;
	return (1);
}
