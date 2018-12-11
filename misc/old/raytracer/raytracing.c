/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:18:15 by toliver           #+#    #+#             */
/*   Updated: 2018/12/01 10:04:55 by toliver          ###   ########.fr       */
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
		t_vec	vec1;
		t_vec	vec2;

		vec1 = vec_add(ray->obj_hit->pos, ray->obj_hit->params.plane.normal);
		vec2 = vec_add(ray->obj_hit->pos, vec_opposite(ray->obj_hit->params.plane.normal));
		if (vec_magnitude(vec_init(ray->origin, vec1)) < vec_magnitude(vec_init(ray->origin, vec2)))
			ray->normal = ray->obj_hit->params.plane.normal; // prendre celle qui fait le plus face au viewer
		else
			ray->normal = vec_opposite(ray->obj_hit->params.plane.normal);
	}
	else if (ray->obj_hit->type == CYLINDER)
	{
		// valeur absolue dotproduct to_hit . cylinderaxis
		t_vec	center_to_hit;
		float	len;
		t_vec	center_under_hit;
		center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos);
		len = vec_dotproduct(center_to_hit, ray->obj_hit->rot);
		center_under_hit = vec_add(ray->obj_hit->pos, vec_mul(ray->obj_hit->rot, len));
		ray->normal = vec_normalize(vec_init(center_under_hit, ray->hit_pos));
	}
	else if (ray->obj_hit->type == CONE)
	{
		t_vec	center_to_hit;
		t_vec	axis1;
		t_vec	axis2;
		t_vec	hit_to_axis1;
		t_vec	hit_to_axis2;
		t_vec	real_axis;
		t_vec	rot_axis;
		t_vec	hypotenuse;
		float	hypotenuse_len;
		t_vec	normal;

		center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos); // a
		axis1 = vec_add(ray->obj_hit->rot, ray->obj_hit->pos);	
		axis2 = vec_add(vec_opposite(ray->obj_hit->rot), ray->obj_hit->pos);
		hit_to_axis1 = vec_init(ray->hit_pos, axis1);
		hit_to_axis2 = vec_init(ray->hit_pos, axis2);
		if (vec_magnitude(hit_to_axis1) < vec_magnitude(hit_to_axis2))
			real_axis = axis1;
		else
			real_axis = axis2;
		real_axis = vec_normalize(vec_sub(real_axis, ray->obj_hit->pos));
		rot_axis = vec_normalize(vec_opposite(vec_crossproduct(vec_normalize(center_to_hit), real_axis)));
		hypotenuse = vec_normalize(matrix_mult_vec(rotmatrix_axis_angle(rot_axis, degtorad(90)), real_axis));
		hypotenuse_len = vec_magnitude(center_to_hit) / cosf(degtorad(90) - ray->obj_hit->params.cone.angle);
		hypotenuse = vec_add(vec_mul(hypotenuse, hypotenuse_len), ray->obj_hit->pos);
		normal = vec_init(ray->hit_pos, hypotenuse);
		normal = vec_normalize(normal);
		ray->normal = normal;
		// marche pas, faire les derivees partielles de fonctions :D
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
//		ray->length -= TOLERANCE;	
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
//		color = ray->obj_hit->color.rgb.value;
		color = colorization(ray, env);
		mlx_px_to_img(env->win->img, x, y, color);
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

	angle = -acos(vec_dotproduct(env->camera->orientation, vec_init0(0,0,1)));
//	if (!isequalfloat(angle, 0.0) && !isequalfloat(fabs(angle), 1.0))
//		angle = acosf(angle);
//	else if (isequalfloat(angle, 1.0))
//		angle = 0;
//	else if (isequalfloat(angle, -1))
//		angle = degtorad(180);
//	else
//		angle = degtorad(90);
	axis = vec_normalize(vec_opposite(vec_crossproduct(env->camera->orientation, vec_init0(0,0,1))));
	if (vec_magnitude(axis) == 0)
		matrix = identity_matrix_init();
	else
		matrix = rotmatrix_axis_angle(axis, -angle);
	a = get_top_left_vec(env->camera, env->win, &xinc, &yinc);
	y = 0;
	while (y < env->win->winy)
	{
		x = 0;
		while (x < env->win->winx)
		{
			// si jamais code marche pas, changer env->camera->pos par vertex_init(0,0,0)
			ray_vec = vec_normalize(vec_init0(a.x + xinc * x, a.y + yinc * y, 1)); // ici remplacer le 1 par la distance du viewplane
			if (angle != NAN)
				ray_vec = vec_normalize(matrix_mult_vec(matrix, ray_vec));
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
