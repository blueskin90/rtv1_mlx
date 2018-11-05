/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:40:18 by nfinkel           #+#    #+#             */
/*   Updated: 2018/11/05 19:04:14 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>
#define WIN_TITLE "test"

void	init_env(t_env *env, t_mlx *mlx, t_cam *cam)
{
	env->mlx = ftx_mlxctor(mlx);
	ftx_winctor(env->mlx, WIN_TITLE, WIN_X, WIN_Y);
	ftx_imgctor(env->mlx, WIN_X, WIN_Y);
	env->height = WIN_Y;
	env->width = WIN_X;
	env->hx = WIN_X / 2;
	env->hy = WIN_Y / 2;
	env->invWidth = 1.0 / (double)env->width;
	env->invHeight = 1.0 / (double)env->height;
	env->light =  ft_v3new(0, 10, -25);
	env->cam = cam;
	cam->fov = 10;
	cam->angle = 0.3; // CA CEST UN ZOOM/FOV
	// TROUVER COMMENT FAIRE L ANGLE DE LA CAM
	//tan(M_PI * 0.5 * cam->fov / 180.0);
	screen_ratio(env->width, env->height, &cam->ratio_x, &cam->ratio_y);
	cam->pt = ft_v3new(0, 0, 0);
	// TESTS
	env->low_light = INFINITY;
	env->high_light = 0;
	env->nbr_light= 0;
	env->total_light = 0;
}

int	main(int argc, const char *argv[])
{
	t_env	env;
	t_mlx	mlx;
	t_cam	cam;

	if (argc == 3)
		exit(-1);
	init_env(&env, &mlx, &cam);
	env.objs = add_objs();
	render(env);
	events_listener(env);
	mlx_loop(mlx.mlx);
	KTHXBYE;
}
