/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:50:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 04:20:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					print_color(t_RGB color, char * name)
{
	printf("%-10s : RGB[%f, %f, %f] HEX : #%X\n", name,
			color.r, color.g, color.b, color.value);
}

void					print_objects(t_obj *obj, char *type)
{
	t_obj			*ptr;
	int				nbr;


	nbr = 1;
	ptr = obj;
	printf("===================== PRINTING %s ===========================\n", type);
	while (ptr)
	{
		printf("=== OBJECT %d === \n", nbr);
		if (ptr->type == PLANE)
		{
			printf("PLAN : \n");
		}
		else if (ptr->type == CONE)
		{
			printf("CONE : \n");
			printf("%-10s : %f\n","angle", ptr->params.cone.angle);
		}
		else if (ptr->type == CYLINDER)
		{
			printf("CYLINDRE : \n");
			printf("%-10s : %f\n", "radius", ptr->params.cylinder.radius);
		}
		else if (ptr->type == SPHERE)
		{
			printf("SPHERE : \n");
			printf("%-10s : %f\n","radius", ptr->params.sphere.radius);
		}
		else if (ptr->type == LIGHT)
		{
			printf("LIGHT : \n");
			printf("%-10s : %f\n","intensity", ptr->params.light.intensity);
		}
		else if (ptr->type == CAMERA)
		{
			printf("CAMERA : \n");
			printf("%-10s : %f\n","fov", ptr->params.camera.fov);
		}
		else
			printf("UNKNOWN TYPE !!!!!!!!: ");
		printf("%-10s : ", "pos");
		print_vec(ptr->pos);
		printf("%-10s : ", "right");
		print_vec(ptr->right);
		printf("%-10s : ", "up");
		print_vec(ptr->up);
		printf("%-10s : ", "dir");
		print_vec(ptr->dir);
		print_color(ptr->color, "color");
		print_color(ptr->specular, "specular");
		print_color(ptr->diffuse, "diffuse");
		printf("%-10s : \n", "world to obj");
		print_matrix(ptr->world_to_obj);
		printf("%-10s : \n", "obj to world ");
		print_matrix(ptr->obj_to_world);
		ptr = ptr->next;
		nbr++;
	}
	printf("================== END OF PRINTING %s =======================\n", type);
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
	print_objects(scene->objs, "OBJECTS");
	print_objects(scene->lights, "LIGHTS");
	print_objects(scene->cameras, "CAMERAS");
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
