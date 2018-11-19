/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/11/19 06:04:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
float g_smallest;
float g_biggest;

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			orientation;
	t_color			color;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	pos = vec_init0(0, 0, 5);
	orientation = vec_init0(0, 0, 1);
	color = color_init_hsl(0xff0000);
	scene->objs = sphere_malloc(pos, 5, orientation, color);
	pos = vec_init0(0, 6 , 5);
	color = color_init_hsl(0x00ff00);
	scene->objs->next = sphere_malloc(pos, 1, orientation, color);
	pos = vec_init0(15, 15, 15);
	color = color_init_hsl(0x0000ff);
	scene->objs->next->next = sphere_malloc(pos, 8, orientation, color);
	color = color_init_hsl(0xff);
	orientation = vec_init0(0, 0, 5);
	pos = vec_init0(0, -1, 5);
	scene->objs->next->next->next = plane_malloc(pos, orientation, color);
	pos = vec_init0(5, 10, 5);
	color = color_init_hsl(0xffffff);
	scene->light = light_malloc(pos, color, 0.6);
	pos = vec_init0(-5, 10, 8);
	scene->light->next = light_malloc(pos, color, 0.9);
	env->scene = scene;
	pos = vec_init0(0, 0, -10);
	orientation = vec_init0(0, 0, 1);
	env->camera = camera_malloc(pos, orientation, 60.0);
	return (1);
}

int					main(void)
{
	t_env			*env;

	g_smallest = INFINITY;
	g_biggest = -INFINITY;
//	test();
	env = env_init();
	parse_scene(env);
	scene_copy(env);
//	if (env->scene)

//	{
//		print_camera(env->camera);
//		print_objets(env->scene);
//		print_objets(env->scene_copy);
//	world_to_cam2(env->camera, env->scene, env->scene_copy);
//		print_camera(env->camera);
//		print_objets(env->scene_copy);
//		exit(1);
//	}
	raytracing(env);
	events_listener(env);
	mlx_loop(env->mlx);
	return (1);
}
