/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:50:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 15:54:33 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					print_objects(t_scene *scene)
{
	t_obj			*ptr;

	ptr = scene->objs;
	printf("===================== PRINTING OBJETS ===========================\n");
	while (ptr)
	{
		if (ptr->type == PLANE)
			printf("PLAN : ");
		else if (ptr->type == CONE)
			printf("CONE : ");
		else if (ptr->type == CYLINDER)
			printf("CYLINDRE : ");
		else if (ptr->type == SPHERE)
			printf("SPHERE : ");
		else
			printf("UNKNOWN TYPE !!!!!!!!: ");
		printf("pos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->dir.x, ptr->dir.y, ptr->dir.z);
		ptr = ptr->next;
	}
	printf("================== END OF PRINTING OBJETS =======================\n");
	printf("\n");
}

void				print_lights(t_scene *scene)
{
	t_obj			*ptr;

	ptr = scene->lights;
	printf("===================== PRINTING LIGHTS ===========================\n");
	while (ptr)
	{
		printf("pos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->dir.x, ptr->dir.y, ptr->dir.z);
		ptr = ptr->next;
	}
	printf("================== END OF PRINTING LIGHTS =======================\n");
	printf("\n");
}

void				print_cameras(t_scene *scene)
{
	t_obj			*ptr;

	ptr = scene->cameras;
	printf("===================== PRINTING CAMERAS ==========================\n");
	while (ptr)
	{
		printf("pos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->dir.x, ptr->dir.y, ptr->dir.z);
		ptr = ptr->next;
	}
	printf("================== END OF PRINTING CAMERAS ======================\n");
	printf("\n");
}

void				print_scene(t_scene *scene)
{
	print_objects(scene);
	print_lights(scene);
	print_cameras(scene);
}

void				print_renderer(t_ray *ray)
{
	int				x;
	int				y;

	y = 0;
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			print_vec(ray[x + y * win_getx()].pos);
			print_vec(ray[x + y * win_getx()].dir);
			x++;
		}
		y++;
	}
}
