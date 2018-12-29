/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:41:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/28 23:53:51 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_obj_hit_infos(t_ray *ray)
{
	printf("	ray has struck : ");
	if (ray->obj_hit->type == SPHERE)
		printf("A SPHERE\n");
	else if (ray->obj_hit->type == PLANE)
		printf("A PLANE\n");
	else if (ray->obj_hit->type == CYLINDER)
		printf("A CYLINDER\n");
	else if (ray->obj_hit->type == CONE)
		printf("A CONE\n");
	else
		printf("SOMETHING (not correct obj_hit->type)\n");
	printf("	which pos is : ");
	print_vec(ray->obj_hit->pos);
	printf("	direction is : ");
	print_vec(ray->obj_hit->dir);
	printf("	and color is : %x\n", ray->obj_hit->color.value);
}

void				print_lightobj_hit_infos(t_ray *ray)
{
	printf("		lightray has struck : ");
	if (ray->obj_hit->type == SPHERE)
		printf("A SPHERE\n");
	else if (ray->obj_hit->type == PLANE)
		printf("A PLANE\n");
	else if (ray->obj_hit->type == CYLINDER)
		printf("A CYLINDER\n");
	else if (ray->obj_hit->type == CONE)
		printf("A CONE\n");
	else
		printf("SOMETHING (not correct obj_hit->type)\n");
	printf("		which pos is : ");
	print_vec(ray->obj_hit->pos);
	printf("		direction is : ");
	print_vec(ray->obj_hit->dir);
	printf("		and color is : %x\n", ray->obj_hit->color.value);
}

void				print_ray(t_ray *ray)
{
	printf("position : ");
	print_vec(ray->pos);
	printf("direction : ");
	print_vec(ray->dir);
	printf("ray color : %x\n", ray->color.value);
	if (ray->obj_hit)
	{
		print_obj_hit_infos(ray);
		printf("normal : ");
		print_vec(ray->normal);
		printf("hit_pos : ");
		print_vec(ray->hit_pos);
		printf("length : %f\n", ray->length);
	}
	else
		printf("ray has gone nowhere\n");
}

void				print_lightray(t_ray *ray)
{
	printf("	position : ");
	print_vec(ray->pos);
	printf("	direction : ");
	print_vec(ray->dir);
	printf("	ray color : %x\n", ray->color.value);
	if (ray->obj_hit)
	{
		print_lightobj_hit_infos(ray);
		printf("	normal : ");
		print_vec(ray->normal);
		printf("	hit_pos : ");
		print_vec(ray->hit_pos);
		printf("	length : %f\n", ray->length);
	}
	else
		printf("		ray has gone nowhere\n");
}

void				display_cursor_lightinfos(t_ray *ray)
{
	t_RGB		finalcolor;
	t_obj		*ptr;
	t_ray		to_light;

	finalcolor = get_ambiant(ray);
	ptr = scene_get()->lights;
	while (ptr)
	{
		to_light = ray_init_lookat(ray->hit_pos, ptr->pos);
		shoot_ray(&to_light);
		printf("	\\\\\\\\\\ LIGHT RAY INFORMATIONS :\n");
		printf("	ray shot from : ");
		print_vec(ray->hit_pos);
		printf(" length to light : %f\n",
				vec_magnitude(vec_init(ray->hit_pos, ptr->pos)));
		print_lightray(&to_light);
		printf("	\\\\\\\\\\ END OF LIGHTRAY INFORMATIONS\n");
		ptr = ptr->next;
	}
}

void				display_cursor_infos(void)
{
	t_ray			*ray;

	ray = renderer_getray(cursor_getx() + cursor_gety() * win_getx());
	printf("\n");
	printf("///////////// RAY INFORMATIONS :\n");
	printf("ray shot at x: %d y: %d\n", cursor_getx(), cursor_gety());
	print_ray(ray);
	display_cursor_lightinfos(ray);
	printf("///////////////// END OF RAY INFORMATIONS\n\n");
}
