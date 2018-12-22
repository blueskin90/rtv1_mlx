/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 00:41:33 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				raytracing_malloc_setting(void)
{
	malloc_renderers();
	scene_set(env_get()->scene); // set la scene actuelle a la premiere
	camera_set(scene_get()->cameras); // set la camera a la premiere;
	renderer_set(); // set le renderer a la camera actuelle;
}

void				raytracing_setting(void)
{
	scene_set(env_get()->scene); // set la scene actuelle a la premiere
	camera_set(scene_get()->cameras); // set la camera a la premiere;
}

int					malloc_rt(void)
{
//	printf("Malloc'd version of RT\n");
	init();
//	printf("initialization done\n");
	parse_scene2(); // puis parsing bidon
//	printf("parsing done\n");

	//
	raytracing_malloc_setting();
//	printf("settings done\n");

	raytracing_malloc();
//	printf("raytracing done\n");

	print_mode_set(RAY_COLOR_MODE);
	printing();
//	printf("printing done\n");

	events_listener();
	mlx_loop(mlx_get());
	return (1);
}

int					stack_rt(char *file)
{
		t_elem	*json;
		
	init();
	json = json_parser(file);
	rtv1_parsing(json);
	//parse_scene2();
	raytracing_setting(); // tout refaire pour que ca fonctionne sur la stack
	print_scene(scene_get());
//	raytracing_stack();
//	mlx_loop(mlx_get());
	return (1);
}

/*
int					main(int ac, char **av)
{

//	t_env			*env;
//	t_elem			*json;

//	env = env_init();
//	env_set(env); // toujours init et set lenv avant tout;
//	parse_2scene(env); // puis parsing bidon
//	json = json_parser(av[1]);
//	env = rtv1_parsing(json, env);
	//scene_set(env->scene); // set la scene actuelle a la premiere
	//camera_set(env->scene->cameras); // set la camera a la premiere;
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
	if (ac != 1)
	{
		printf("stack\n");
		stack_rt(av[1]);
	}
	else
	{
		printf("malloc\n");
		malloc_rt();
	}
	return (1);
}
*/
void			settings(void)
{
	return;
}

void			running(void)
{
	return;
}

void			parsing(void)
{
	parse_scene2();
}

int				main(int ac, char **av)
{
	args_parsing(ac, av);
	init();
	parsing();
	settings();
	running();
	return (1);
}
