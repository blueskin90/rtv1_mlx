/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 02:21:04 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
void			print_renderers(void)
{
	ft_printf("faire la fonction qui print les renderers, feignasse !\n");
}

void			print_settings(void)
{
	t_scene		*scene;
	t_obj		*camera;

	scene = scene_get();
	camera = camera_get();
	if (!scene)
		ft_printf("	scene is still not set !\n");
	else
		ft_printf("	scene name is : %s\n", scene->name);
	if (!camera)
		ft_printf("	rendering camera is still not set !\n");
	else
		ft_printf("	rendering camera is set\n");
	if (renderer_mode_get() != STACK)
		print_renderers();
}

void			renderers_init(void)
{
	if (renderer_mode_get() == MALLOC)
		malloc_renderers();
	else
		ft_printf("QUE FAIRE ? POUR LES AUTRES INITIALISATIONS DE RENDERERS\n");
}

void			settings(void)
{
	step_set(SETTINGS);
	scene_set(env_get()->scene);
	camera_set(scene_get()->cameras);
	if (renderer_mode_get() != 0)
	{
		renderer_set();
		renderers_init();
	}
	verbose();
	return ;
}

void			print_running(void)
{
	ft_printf("faire la fonction qui print le running verbose feignasse !\n");
}

void			running(void)
{
	step_set(RUNNING);
	if (renderer_mode_get() == STACK)
	{
		raytracing_stack();
		mlx_loop(mlx_get());
	}
	else if (renderer_mode_get() == MALLOC)
	{
		raytracing_malloc();
		print_mode_set(RAY_COLOR_MODE);
		printing();
		mlx_loop(mlx_get());
	}
	verbose();
	return ;
}

*/
int				main(int ac, char **av)
{
	t_args		*args;
	t_env		*env;

	args = args_parsing(ac, av);
	env = init(args);
	env->scene = parsing(args);
	settings(args, env);
	running(args, env->scene);
	printing(args, env->scene, env->win, env->mlx);
	return (1);
}
