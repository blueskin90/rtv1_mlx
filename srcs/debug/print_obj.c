/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:50:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 00:55:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					print_color(t_RGB color, char * name)
{
	printf("%s : RGB[%f, %f, %f] HEX : #%X\n", name,
			color.r, color.g, color.b, color.value);
}

void					print_objects(t_scene *scene)
{
	t_obj			*ptr;

	ptr = scene->objs;
	printf("===================== PRINTING OBJETS ===========================\n");
	while (ptr)
	{
		if (ptr->type == PLANE)
		{
			printf("PLAN : \n");
		}
		else if (ptr->type == CONE)
		{
			printf("CONE : \n");
			printf("angle : %f\n", ptr->params.cone.angle);
		}
		else if (ptr->type == CYLINDER)
		{
			printf("CYLINDRE : \n");
			printf("radius : %f\n", ptr->params.cylinder.radius);
		}
		else if (ptr->type == SPHERE)
		{
			printf("SPHERE : \n");
			printf("radius : %f\n", ptr->params.sphere.radius);
		}
		else
			printf("UNKNOWN TYPE !!!!!!!!: ");
		printf("pos : ");
		print_vec(ptr->pos);
		printf("right : ");
		print_vec(ptr->right);
		printf("up : ");
		print_vec(ptr->up);
		printf("dir : ");
		print_vec(ptr->dir);
		printf("pos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->dir.x, ptr->dir.y, ptr->dir.z);
		print_color(ptr->color, "color");
		print_color(ptr->specular, "specular");
		print_color(ptr->diffuse, "diffuse");
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

void				print_new_scene(t_scene *scene)
{
	printf("===================== PRINTING SCENE ==========================\n");
	printf("name : %s\n", scene->name);
	print_objects(scene);
	print_lights(scene);
	print_cameras(scene);
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
