/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:18:15 by toliver           #+#    #+#             */
/*   Updated: 2018/11/18 22:47:11 by cvermand         ###   ########.fr       */
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

t_vec		get_top_left_vec(t_camera *cam, t_win *window, float *xinc, float *yinc)
{
	float		x;
	float		y;
	float		half_fovrad;

	half_fovrad = degtorad(cam->fov * 0.5);
	y = tanf(half_fovrad);
	x = -y * (window->winx / (float)window->winy);
	*xinc = -x / ((float)window->winx / 2.0);
	*yinc = -y / ((float)window->winy / 2.0);
	return (vec_init0(x + (*xinc / 2), y + (*yinc / 2), 1));
}

float			shoot_ray(t_ray ray, t_env *env, t_obj **objs_hit)
{
	t_obj	 	*objs_ptr;
//	t_obj		*objs_hit;
	float		nearest_hit;
	float		current_hit;

	nearest_hit = INFINITY;
	objs_ptr = env->scene_copy->objs;
	while (objs_ptr)
	{
		if ((current_hit = objs_ptr->intersect(ray, objs_ptr)) != INFINITY 
				&& current_hit < nearest_hit)
		{
			(*objs_hit) = objs_ptr;
			nearest_hit = current_hit;
		}
		objs_ptr = objs_ptr->next;
	}
	return (nearest_hit);
}

int				tracing(t_ray ray, t_env *env, int x, int y)
{
	t_obj		*objs_hit;
	float		nearest_hit;
	int			color;
	
	//objs_hit = NULL;
	nearest_hit = shoot_ray(ray, env, &objs_hit);
	if (nearest_hit != INFINITY)
	{
		color = colorization(env, ray, nearest_hit, objs_hit);
		mlx_px_to_img(env->win->img, x, y, color);
//		mlx_px_to_img(env->win->img, x, y, objs_hit->color.rgb.value);
	}
	else 
		mlx_px_to_img(env->win->img, x, y, 0x000000);
	return (1);
}

int				raytracing(t_env *env)
{
	t_vec	a;
	float		xinc;
	float		yinc;
	int			x;
	int			y;
	t_vec	ray_vec;
	t_ray		ray;

	a = get_top_left_vec(env->camera, env->win, &xinc, &yinc);
	y = 0;
	while (y < env->win->winy)
	{
		x = 0;
		while (x < env->win->winx)
		{
			// si jamais code marche pas, changer env->camera->pos par vertex_init(0,0,0)
			ray_vec = vec_normalize(vec_init0(a.x + xinc * x, a.y + yinc * y, 1));
			ray = ray_init(env->camera->pos, ray_vec);
			tracing(ray, env, x, y);
			// ICI COULEUR
			x++;
		}
		y++;
	}
	printf("smallest : %f, biggest : %f\n", g_smallest, g_biggest);
	g_smallest = 0;
	g_biggest = 0;
	mlx_put_image_to_window(env->mlx, env->win->winptr, env->win->img->imgptr, 0, 0);
	return (1);
}
