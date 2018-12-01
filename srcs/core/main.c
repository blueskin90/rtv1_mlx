/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/01 17:20:20 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void				obj_add(t_scene *scene, t_obj *obj)
{
	t_obj			*ptr;

	ptr = scene->objs;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = obj;
	}
	else
		scene->objs = obj;
}

void				light_add(t_scene *scene, t_obj *light)
{
	t_obj			*ptr;

	ptr = scene->lights;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = light;
	}
	else
		scene->lights = light;
}

void				camera_add(t_scene *scene, t_obj *camera)
{
	t_obj			*ptr;

	ptr = scene->cameras;
	if (ptr)
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = camera;
	}
	else
		scene->cameras = camera;
}

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vec			pos;
	t_vec			lookat;
	t_color			color;
	t_obj			*objptr;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));

	// 10 obj
	pos = vec_init0(-5, 0, 0);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0xa610ff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 5);
	obj_add(scene, objptr);
	
	pos = vec_init0(-5, 0, 10);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0xffaaaa);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 5);
	obj_add(scene, objptr);


	pos = vec_init0(10, 0, 0);
	lookat = vec_init0(0, 0, 6);
	color = color_init_hsl(0x10ff10);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 7);
	obj_add(scene, objptr);


	pos = vec_init0(-10, 5, 20);
	color = color_init_hsl(0x30ff30);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 1.0);
	obj_add(scene, objptr);

	pos = vec_init0(0, 0, 0);
	color = color_init_hsl(0x8080ff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_sphere_params(objptr, 3);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, -9, 0);
	pos = vec_init0(0, -10, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	lookat = vec_init0(6, 6, 6);
	pos = vec_init0(5, 5, 5);
	color = color_init_hsl(0xaaff00);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cylinder_params(objptr, 1);
	obj_add(scene, objptr);

	pos = vec_init0(-10, 0, 20);
	lookat = vec_init0(-11, 1, 21);
	color = color_init_hsl(0xff5050);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_cone_params(objptr, 22);
	obj_add(scene, objptr);
	
	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, 50, 0);
	pos = vec_init0(0, 51, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(49, 0, 0);
	pos = vec_init0(50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(-49, 0, 0);
	pos = vec_init0(-50, 0, 0);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

	color = color_init_hsl(0xaabbcc);
	lookat = vec_init0(0, 0, 50);
	pos = vec_init0(0, 0, 49);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_plane_params(objptr);
	obj_add(scene, objptr);

// 2 lights

	lookat = vec_init0(0, -3, 1);
	pos = vec_init0(15, 25, -15);
	color = color_init_hsl(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.6);
	light_add(scene, objptr);

	pos = vec_init0(-15, 25, -15);
	color = color_init_hsl(0xffffff);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_light_params(objptr, 0.9);
	light_add(scene, objptr);

// 1 camera

	env->scene = scene;
	pos = vec_init0(0, 15, -100);
	lookat = vec_init0(0, 0, 5);
	objptr = obj_malloc_lookat(pos, lookat, vec_y(), color);
	obj_camera_params(objptr, 60.0);
	camera_add(scene, objptr);
	return (1);
}
// pas dans le .h
void				get_normal(t_ray *ray)
{
	if (ray->obj_hit->type == SPHERE)
		ray->normal = vec_norm(vec_init(ray->obj_hit->pos, ray->hit_pos));
	else if (ray->obj_hit->type == PLANE)
	{
		t_vec	vec1;
		t_vec	vec2;

		vec1 = vec_add(ray->obj_hit->pos, ray->obj_hit->dir);
		vec2 = vec_add(ray->obj_hit->pos, vec_opposite(ray->obj_hit->dir));
		if (vec_magnitude(vec_init(ray->pos, vec1)) < vec_magnitude(vec_init(ray->pos, vec2)))
			ray->normal = ray->obj_hit->dir; // prendre celle qui fait le plus face au viewer
		else
			ray->normal = vec_opposite(ray->obj_hit->dir);
	}
	else if (ray->obj_hit->type == CYLINDER)
	{
		// valeur absolue dotproduct to_hit . cylinderaxis
		t_vec	center_to_hit;
		float	len;
		t_vec	center_under_hit;
		center_to_hit = vec_init(ray->obj_hit->pos, ray->hit_pos);
		len = vec_dotproduct(center_to_hit, ray->obj_hit->dir);
		center_under_hit = vec_add(ray->obj_hit->pos, vec_mul(ray->obj_hit->dir, len));
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
		axis1 = vec_add(ray->obj_hit->dir, ray->obj_hit->pos);	
		axis2 = vec_add(vec_opposite(ray->obj_hit->dir), ray->obj_hit->pos);
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
		ray->normal = ray->obj_hit->dir;
}

void				shoot_ray(t_ray *ray)
{
	t_obj			*objptr;
	float			current_hit;

	current_hit = INFINITY;
	objptr = scene_get()->objs;
	while (objptr)
	{

		if ((current_hit = objptr->intersect(*ray, objptr)) != INFINITY
			&& current_hit < ray->length)
		{
			ray->obj_hit = objptr;
			ray->length = current_hit;
		}
		objptr = objptr->next;
	}
	if (ray->length != INFINITY)
	{
		ray->hit_pos = vec_add(ray->pos, vec_mul(ray->dir, ray->length));
		get_normal(ray);
	}
}

void				raytracing(void)
{
	int				i;

	i = 0;
	while (i < renderer_getraymax())
	{
		shoot_ray(renderer_getray(i)); 
		i++;
	}
}

void				printing(void)
{
	int				x;
	int				y;
	t_ray			*ray;
	float			multvalue;
	int				color;

	y = 0;
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			ray = renderer_getray(x + y * win_getx());
			if (ray->length != INFINITY)
			{
				/*
				if (ray->length > 255)
					multvalue = 1;
				else if (ray->length < 0)
					multvalue = 0;
				else
					multvalue = ray->length / 255.0;
					*/
//				color = get_rgb(ray->obj_hit->color.rgb.r * (1 - multvalue), ray->obj_hit->color.rgb.g * (1 - multvalue), ray->obj_hit->color.rgb.b * (1 - multvalue));
//				color = ray->obj_hit->color.rgb.value; 
				color = colorization(ray, env_get());
				mlx_px_to_img(env_get()->win->img, x, y, color);
			}
			else
				mlx_px_to_img(env_get()->win->img, x, y, 0x000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_get(), win_get()->winptr, win_get()->img->imgptr, 0, 0);
}

int					main(int ac, char **av)
{
	t_env			*env;

	env = env_init();
	env_set(env); // toujours init et set lenv avant tout;
	parse_scene(env); // puis parsing bidon
//	print_angles(); // affichage statique de valeurs d'angles pratiques
//	print_scene(env->scene); // affichage scene pour verifier
	scene_set(env->scene); // set la scene actuelle a la premiere
	camera_set(env->scene->cameras); // set la camera a la premiere;
	renderer_set(); // set le renderer a la camera actuelle;
	printf("settings done\n");
	raytracing();
	printf("raytracing done\n");
	printing();
	printf("printing done\n");
//	print_renderer(renderer_get());
	events_listener(env);
	mlx_loop(mlx_get());
	(void)ac;
	(void)av;
	return (1);
}
