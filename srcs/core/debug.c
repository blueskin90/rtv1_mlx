/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:41:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/10 18:37:50 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_angles(void)
{
	int				angle;

	angle = -360;
	while (angle <= 360)
	{
		printf("cos : %d degree = %f rad = %f\n", angle, cosf(degtorad(angle)), degtorad(angle));
		angle +=45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("sin : %d degree = %f rad = %f\n", angle, sinf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("tan : %d degree = %f rad = %f\n", angle, tanf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
}

void			print_matrix(t_matrix m)
{
	printf("| %5f %5f %5f %5f |\n", m.matrix[0][0],m.matrix[0][1],m.matrix[0][2],m.matrix[0][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[1][0],m.matrix[1][1],m.matrix[1][2],m.matrix[1][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[2][0],m.matrix[2][1],m.matrix[2][2],m.matrix[2][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[3][0],m.matrix[3][1],m.matrix[3][2],m.matrix[3][3]);
	printf("\n");
}
void					print_color(t_obj *obj, char * name)
{
		t_RGB	*color;

		color = &obj->color;
		if (color != NULL)
		{
			printf("%s : RGB[%f, %f, %f] HEX : #%X\n", name,
							color->r, color->g, color->b, color->value);
		}
		else {
			printf("NO COLOR\n");
		}

}

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
		print_color(ptr, "color");
		print_color(ptr, "specular");
		print_color(ptr, "diffuse");
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

void				print_vec(t_vec v)
{
	printf("[%f][%f][%f] [%f]\n", v.x, v.y, v.z, v.w);
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

void				print_to_light_infos(t_ray *ray)
{
	(void)ray;
}

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
	print_to_light_infos(ray);
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

	finalcolor = get_ambiant(ray); // pas sur que ce soit logique de ne pas prendre en compte les lumieres actuelles
	ptr = scene_get()->lights;
	while (ptr)
	{
		to_light = ray_init_lookat(ray->hit_pos, ptr->pos);
		shoot_ray(&to_light);
		printf("	\\\\\\\\\\ LIGHT RAY INFORMATIONS :\n");
		printf("	ray shot from : ");
		print_vec(ray->hit_pos);
		printf(" length to light : %f\n", vec_magnitude(vec_init(ray->hit_pos, ptr->pos)));
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
