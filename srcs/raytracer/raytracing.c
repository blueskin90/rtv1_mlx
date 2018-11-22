/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:18:15 by toliver           #+#    #+#             */
/*   Updated: 2018/11/22 04:58:54 by toliver          ###   ########.fr       */
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

int				get_normal(t_ray *ray)
{
	if (ray->obj_hit->type == SPHERE)
		ray->normal = vec_norm(vec_init(ray->obj_hit->pos, ray->hit_pos));
	else if (ray->obj_hit->type == PLANE)
	{
		ray->normal = vec_norm(ray->obj_hit->params.plane.normal); // prendre celle qui fait le plus face au viewer
	}
	else if (ray->obj_hit->type == CYLINDER)
	{
		ray->normal = vec_normalize(vec_add(vec_init0(ray->hit_pos.x, 0, ray->hit_pos.z), vec_opposite(vec_init0(ray->obj_hit->pos.x, 0, ray->obj_hit->pos.z))));
	}
	else
		ray->normal = ray->obj_hit->rot;
	return (1);
}

int				shoot_ray(t_ray *ray, t_scene *scene)
{
	t_obj	 	*objs_ptr;
	float		current_hit;

	objs_ptr = scene->objs;
	while (objs_ptr)
	{
		if ((current_hit = objs_ptr->intersect(*ray, objs_ptr)) != INFINITY 
				&& current_hit < ray->length)
		{
			ray->obj_hit = objs_ptr;
			ray->length = current_hit;
		}
		objs_ptr = objs_ptr->next;
	}
	if (ray->length != INFINITY)
	{
		ray->length -= TOLERANCE;	
		ray->hit_pos = vec_add(ray->origin, vec_mul(ray->direction, ray->length));
		get_normal(ray);
	}
	return ((ray->length != INFINITY) ? 1 : 0);
}

int				tracing(t_ray *ray, t_env *env, int x, int y)
{
	int			color;
	
	//objs_hit = NULL;
	shoot_ray(ray, env->scene);
	if (ray->length != INFINITY)
	{
//		color = colorization(env, *ray, ray->length, ray->obj_hit);
		color = colorization(ray, env);
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

	t_vec		axis;
	float		angle;
	t_matrix	matrix;

	angle = vec_dotproduct(env->camera->orientation, vec_init0(0,0,1));
	if (!isequalfloat(angle, 0.0) && !isequalfloat(fabs(angle), 1.0))
		angle = acosf(angle);
	else if (isequalfloat(angle, 1.0))
		angle = 0;
	else if (isequalfloat(angle, -1))
		angle = degtorad(180);
	else
		angle = degtorad(90);
	axis = vec_crossproduct(env->camera->orientation, vec_init0(0,0,1));
	matrix = rotmatrix_axis_angle(axis, -angle);
	a = get_top_left_vec(env->camera, env->win, &xinc, &yinc);
	y = 0;
	while (y < env->win->winy)
	{
		x = 0;
		while (x < env->win->winx)
		{
			// si jamais code marche pas, changer env->camera->pos par vertex_init(0,0,0)
			ray_vec = vec_normalize(vec_init0(a.x + xinc * x, a.y + yinc * y, 1));
			ray_vec = matrix_mult_vec(matrix, ray_vec);
			ray = ray_init(env->camera->pos, ray_vec);
			tracing(&ray, env, x, y);
			// ICI COULEUR
			x++;
		}
		y++;
	}
//	printf("smallest : %f, biggest : %f\n", g_smallest, g_biggest);
	mlx_put_image_to_window(env->mlx, env->win->winptr, env->win->img->imgptr, 0, 0);
	return (1);
}
