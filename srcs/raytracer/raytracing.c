/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:18:15 by toliver           #+#    #+#             */
/*   Updated: 2018/11/10 19:42:26 by cvermand         ###   ########.fr       */
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

t_vertex		get_top_left_vertex(t_camera *cam, t_win *window, float *xinc,
				float *yinc)
{
	float		x;
	float		y;
	float		half_fovrad;

	half_fovrad = degtorad(cam->fov * 0.5);
	x = -tanf(half_fovrad * (float)((float)window->winx / (float)window->winy));
	y = tanf(half_fovrad);
	*xinc = -x / ((float)window->winx / 2.0);
	*yinc = -y / ((float)window->winy / 2.0);
	return (vertex_init(x + (*xinc / 2), y + (*yinc / 2), 1));
}

int				tracing(t_vector ray, t_env *env, int x, int y)
{
	t_sphere 	*objs_ptr;
	t_sphere	*objs_hit;
	float		nearest_hit;
	float		current_hit;
	
	nearest_hit = INFINITY;
	objs_hit = NULL;
	objs_ptr = env->scene->sphere;
	while (objs_ptr)
	{
		if ((current_hit = sphere_intersection(objs_ptr, ray)) != INFINITY 
				&& current_hit < nearest_hit)
		{
			objs_hit = objs_ptr;
			nearest_hit = current_hit;
		}
		objs_ptr = objs_ptr->next;
	}
	if (nearest_hit != INFINITY)
	{
//		printf("%#x\n", objs_hit->color.rgb.value);
		mlx_px_to_img(env->win->img, x, y, objs_hit->color.rgb.value);
	}
	else 
		mlx_px_to_img(env->win->img, x, y, 0x000000);
	return (1);
}

int				raytracing(t_env *env)
{
	t_vertex	a;
	float		xinc;
	float		yinc;
	int			x;
	int			y;
	t_vector	ray;

	a = get_top_left_vertex(env->camera, env->win, &xinc, &yinc);
	printf("[%f][%f][%f] xinc = %f, yinc = %f\n", a.x, a.y, a.z, xinc, yinc);
	y = 0;
	while (y < env->win->winy)
	{
		x = 0;
		while (x < env->win->winx)
		{
			// si jamais code marche pas, changer env->camera->pos par vertex_init(0,0,0)
			ray = vector_normalize(vector_init(vertex_init(0, 0, 0), vertex_init(a.x + xinc * x, a.y + yinc * y, 1)));
	//		if (y == 0 || y == env->win->winy - 1)
	//			printf("[%.30f][%.30f][%.30f] x %d y %d\n", ray.x, ray.y, ray.z, x, y);
			tracing(ray, env, x, y);
			x++;
		}
		y++;
	}
	printf("zlkdjlskdjaslkds %d\n", X_KEYPRESS);
	printf("fini\n");
//	renderer(env->scene, env->camera, env->win->img);
	mlx_put_image_to_window(env->mlx, env->win->winptr, env->win->img->imgptr, 0, 0);
	events_listener(env);
	mlx_loop(env->mlx);
	return (1);
}
