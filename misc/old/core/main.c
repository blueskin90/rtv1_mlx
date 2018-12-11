/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/01 02:20:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
float g_smallest;
float g_biggest;

int					obj_add(t_scene *scene, t_obj *obj)
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
	return (1);
}

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			orientation;
	t_color			color;
	t_obj			*objptr;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	ft_bzero(scene, sizeof(t_scene));

	pos = vec_init0(0, 0, 5);
	orientation = vec_init0(0, 0, 1);
	color = color_init_hsl(0xa610ff);
//	objptr = sphere_malloc(pos, 5, orientation, color);
//	scene->objs = objptr;

	pos = vec_init0(-10, 5, 20);
	color = color_init_hsl(0x30ff30);
//	objptr = sphere_malloc(pos, 1, orientation, color);
//	obj_add(scene, objptr);

	pos = vec_init0(0, 0, 0);
	color = color_init_hsl(0x8080ff);
	objptr = sphere_malloc(pos, 1, orientation, color);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(0, -4, 0);
	pos = vec_init0(0, -5, 0);
	objptr = plane_malloc(pos, orientation, color);
//	scene->objs = objptr;
	obj_add(scene, objptr);

	orientation = vec_init0(6, 6, 6);
	pos = vec_init0(5, 5, 5);
	color = color_init_hsl(0xaaff00);
	objptr = cylinder_malloc(pos, 1, orientation, color);
//	obj_add(scene, objptr);


	pos = vec_init0(-10, 0, 20);
	orientation = vec_init0(-11, 1, 21);
	color = color_init_hsl(0xff5050);
	objptr = cone_malloc(pos, degtorad(22), orientation, color);
	obj_add(scene, objptr);

	/*
	pos = vec_init0(10, 0, -20);
	orientation = vec_init0(-1, 1, 1);
	color = color_init_hsl(0xff3030);
	objptr = cone_malloc(pos, degtorad(22), orientation, color);
	obj_add(scene, objptr);
*/
	pos = vec_init0(-5, 25, -15);
	orientation = vec_init0(-6, 26, -14);
	color = color_init_hsl(0xffffff);
	objptr = cone_malloc(pos, degtorad(22), orientation, color);
//	obj_add(scene, objptr);

	pos = vec_init0(5, 25, -15);
	orientation = vec_init0(4, 26, -14);
	color = color_init_hsl(0xffffff);
	objptr = cone_malloc(pos, degtorad(22), orientation, color);
//`	obj_add(scene, objptr);


	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(0, 50, 0);
	pos = vec_init0(0, 51, 0);
	objptr = plane_malloc(pos, orientation, color);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(49, 0, 0);
	pos = vec_init0(50, 0, 0);
	objptr = plane_malloc(pos, orientation, color);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(-49, 0, 0);
	pos = vec_init0(-50, 0, 0);
	objptr = plane_malloc(pos, orientation, color);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(0, 0, 50);
	pos = vec_init0(0, 0, 49);
	objptr = plane_malloc(pos, orientation, color);
	obj_add(scene, objptr);
	
	pos = vec_init0(-5, 25, -10);
	color = color_init_hsl(0xffffff);
	objptr = sphere_malloc(pos, 1, orientation, color);
//	obj_add(scene, objptr);

	pos = vec_init0(5, 25, -10);
	color = color_init_hsl(0xffffff);
	objptr = sphere_malloc(pos, 1, orientation, color);
//	obj_add(scene, objptr);


	orientation = vec_init0(0, -3, 1);
	pos = vec_init0(5, 25, -15);
	color = color_init_hsl(0xffffff);
	scene->light = light_malloc(pos, color, 0.6);

	pos = vec_init0(-5, 25, -15);
	color = color_init_hsl(0xffffff);
//	scene->light->next = light_malloc(pos, color, 0.9);

	env->scene = scene;

	pos = vec_init0(0, 15, -100);
	orientation = vec_init0(0, 0, 5);
	env->camera = camera_malloc(pos, orientation, 60.0);
	return (1);
}
int					main(int ac, char **av)
{
	t_env			*env;

	(void)av;
	if (ac == 1)
	{
		env = env_init();
		parse_scene(env);
//		scene_copy(env);
		raytracing(env);
		events_listener(env);
		mlx_loop(env->mlx);
	}
	else
	{
		debug_mode(av + 1);
	}
	return (1);
}
