/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/11/09 19:05:46 by cvermand         ###   ########.fr       */
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
	pos = vertex_init(10, 10, 10);
	orientation = vector_init(vertex_init(0, 0, 0), vertex_init(0, 0, 1));
	color = color_init(0xff00ff);
	scene->sphere = sphere_malloc(pos, 3.0, orientation, color);
	pos = vertex_init(-10, -5, 0);
	scene->sphere->next = sphere_malloc(pos, 2.0, orientation, color);
	pos = vertex_init(20, -10, 2);
	scene->sphere->next->next = sphere_malloc(pos, 6.0, orientation, color);
	pos = vertex_init(20, 0, 10);
	color = color_init(0xffffff);
	scene->light = light_malloc(pos, color);
	pos = vertex_init(-5, 0.2, 3.6);
	scene->light->next = light_malloc(pos, color);
	env->scene = scene;
	pos = vertex_init(10, 5, 1);
	orientation.z = -1;
	orientation.y = 0;
	orientation.x = 0;
	env->camera = camera_malloc(pos, orientation);
	return (1);
}



int					main(void)
{
	t_env			*env;

//	test();
	env = env_init();
	parse_scene(env);
	scene_copy(env);
	if (env->scene)
	{
		print_camera(env->camera);
		print_objets(env->scene);
		world_to_cam2(env->camera, env->scene_copy);
		print_camera(env->camera);
		print_objets(env->scene_copy);
		exit(1);
	}
	raytracing(env);
	return (1);
}
