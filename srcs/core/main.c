/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/04 18:12:54 by cvermand         ###   ########.fr       */
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
	color = color_init_hsl(0xa610ff);
	scene->objs = sphere_malloc(pos, 5, orientation, color);

	pos = vec_init0(-10, 5, 20);
	color = color_init_hsl(0x30ff30);
	scene->objs->next = sphere_malloc(pos, 1, orientation, color);

	pos = vec_init0(-25, 0, 5);
	color = color_init_hsl(0x3030ff);
	scene->objs->next->next = sphere_malloc(pos, 8, orientation, color);

	color = color_init_hsl(0xaabbcc);
	orientation = vec_init0(0, 1, 5);
	pos = vec_init0(0, 0, 5);
	scene->objs->next->next->next = plane_malloc(pos, orientation, color);

	orientation = vec_init0(7, 7, 8);
	pos = vec_init0(6, 6, 5);
	color = color_init_hsl(0xaaff00);
	scene->objs->next->next->next->next = cylinder_malloc(pos, 1, orientation, color);

	pos = vec_init0(-10, 5, 20);
	orientation = vec_init0(-11, 6, 20);
	color = color_init_hsl(0xff0000);
	scene->objs->next->next->next->next->next = cone_malloc(pos, degtorad(22), orientation, color);

	orientation = vec_init0(0, -3, 1);
	pos = vec_init0(5, 10, 5);
	color = color_init_hsl(0xffffff);
	scene->light = light_malloc(pos, color, 0.6);

	pos = vec_init0(-5, 10, 8);
	scene->light->next = light_malloc(pos, color, 0.9);

	env->scene = scene;

	pos = vec_init0(0, 15, -50);
	orientation = vec_init0(0, 0, 5);
	env->camera = camera_malloc(pos, orientation, 60.0);
	return (1);
}

void				angles_print(void)
{
	int				angle;

	angle = -360;
	while (angle <= 360)
	{
		printf("cos : %d degree = %f rad = %f\n", angle, cosf(degtorad(angle)), degtorad(angle));
		angle +=45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("sin : %d degree = %f rad = %f\n", angle, sinf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("tan : %d degree = %f rad = %f\n", angle, tanf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
}

int					main(int ac, char **av)
{
	t_env			*env;
	t_elem			*json;

	(void)ac;
	// rajouter test AC
	angles_print();
	env = env_init();
	parse_scene(env);
	json = json_parser(av[1]);
	env = rtv1_parsing(json, env);
	printf("%-5d\n", 123456);
	//raytracing(env);
	events_listener(env);
	mlx_loop(env->mlx);
	return (1);
}
