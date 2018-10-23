/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:18:15 by toliver           #+#    #+#             */
/*   Updated: 2018/10/22 11:57:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mlx_px_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x * 4 + y * img->width * 4] = (color & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 1] = ((color >> 8) & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 2] = ((color >> 16) & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 3] = 0;
}

int		shootray(t_ray ray, t_scene *scene)
{
	(void)ray;
	(void)scene;
	return (0xffffff);	
}

int				renderer(t_scene *scene, t_camera *camera, t_img *img)
{
	int			x;
	int			y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			if ((x > 200 && x < 600) && (y > 100 && y < 500))
				mlx_px_to_img(img, x, y, 0xff0000);
			else
				mlx_px_to_img(img, x, y, 0x00ffff);
			x++;
		}
		y++;
	}
	(void)scene;
	(void)camera;
	return (1);
}

int				raytracing(t_env *env)
{
	t_scene		scene;
	t_camera	camera;
	t_sphere	test;
	t_light		light;

	test.radius = 10;
	test.center = vertex_init(10, 20, 30);
	test.next = NULL;
	camera.pos = vertex_init(0, 0, 0);
	camera.orientation = vector_init(camera.pos, vertex_init(0, 0, 1));
	light.pos = vertex_init(40, 40, 40);
	light.next = NULL;
	scene.sphere = &test;
	scene.light = &light;
	renderer(&scene, &camera, env->win->img);
	mlx_put_image_to_window(env->mlx, env->win->winptr, env->win->img->imgptr, 0, 0);
	mlx_loop(env->mlx);
	return (1);
}
