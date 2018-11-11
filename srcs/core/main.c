/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/11/12 00:18:12 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vertex		pos;
	t_vector		orientation;
	t_color			color;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	pos = vertex_init(0, 0, 5);
	orientation = vector_init(vertex_init(0, 0, 0), vertex_init(0, 0, 1));
	color = color_init(0xff0000);
	scene->sphere = sphere_malloc(pos, 2, orientation, color);
	pos = vertex_init(0, 0, 10);
	color = color_init(0x00ff00);
	scene->sphere->next = sphere_malloc(pos, 2, orientation, color);
	pos = vertex_init(0, 0, 15);
	color = color_init(0x0000ff);
	scene->sphere->next->next = sphere_malloc(pos, 2, orientation, color);
	pos = vertex_init(20, 0, 10);
	color = color_init(0xffffff);
	scene->light = light_malloc(pos, color);
	pos = vertex_init(-5, 0.2, -3.6);
	scene->light->next = light_malloc(pos, color);
	env->scene = scene;
	pos = vertex_init(0, 0, 0);
	orientation.z = 1;
	orientation.y = 0;
	orientation.x = 0;
	env->camera = camera_malloc(pos, orientation, 60.0);
	return (1);
}

int					main(void)
{
	t_env			*env;

//	test();
	env = env_init();
	parse_scene(env);
	scene_copy(env);
//	if (env->scene)

//	{
//		print_camera(env->camera);
//		print_objets(env->scene);
//		print_objets(env->scene_copy);
	world_to_cam2(env->camera, env->scene, env->scene_copy);
//		print_camera(env->camera);
//		print_objets(env->scene_copy);
//		exit(1);
//	}
	raytracing(env);
	events_listener(env);
	mlx_loop(env->mlx);
	return (1);
}
