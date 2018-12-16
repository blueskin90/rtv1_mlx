/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/16 16:28:43 by toliver          ###   ########.fr       */
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
	parse_scene(); // puis parsing bidon
//	printf("parsing done\n");
	raytracing_malloc_setting();
//	printf("settings done\n");

	raytracing_malloc();
//	printf("raytracing done\n");

	printing();
//	printf("printing done\n");

//	events_listener();
//	mlx_loop(mlx_get());
	return (1);
}

int					stack_rt(void)
{
	init();
	parse_scene();
	raytracing_setting(); // tout refaire pour que ca fonctionne sur la stack
	raytracing_stack();
//	mlx_loop(mlx_get());
	return (1);
}

int					main(int ac, char **av)
{
	(void)av;
	if (ac == 1)
	{
		printf("stack\n");
		stack_rt();
	}
	else
	{
		printf("malloc\n");
		malloc_rt();
	}
	return (1);
}
