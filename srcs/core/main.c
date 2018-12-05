/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/05 17:45:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
float g_smallest;
float g_biggest;


int					main(int ac, char **av)
{
	t_env			*env;
	t_elem			*json;

	env = env_init();
	env_set(env); // toujours init et set lenv avant tout;
//	parse_2scene(env); // puis parsing bidon
	json = json_parser(av[1]);
	env = rtv1_parsing(json, env);
	//scene_set(env->scene); // set la scene actuelle a la premiere
	//camera_set(env->scene->cameras); // set la camera a la premiere;
	/*renderer_set(); // set le renderer a la camera actuelle;
	printf("settings done\n");
	raytracing();
	printf("raytracing first pass done\n");
	raytracing_lights();
	printf("raytracing lights pass done\n");
	printing();
	printf("printing done\n");
	events_listener(env);
	mlx_loop(mlx_get());*/
	(void)ac;
	(void)av;
	return (1);
}
