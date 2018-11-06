/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 23:09:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					test(void)
{
	t_vertex vtx0 = vertex_init(0, 0, 0);
	t_vertex vtxX = vertex_init(1, 0, 0);
	t_vertex vtxY = vertex_init(0, 1, 0);
	t_vertex vtxZ = vertex_init(0, 0, 1);

	t_vector vtcXunit = vector_init(vtx0, vtxX);
	t_vector vtcYunit = vector_init(vtx0, vtxY);
	t_vector vtcZunit = vector_init(vtx0, vtxZ);
	t_vector vtc0unit = vector_init(vtx0, vtx0);

	printf("x = %f, y = %f, z = %f\n", vtcXunit.x, vtcXunit.y, vtcXunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcYunit.x, vtcYunit.y, vtcYunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcZunit.x, vtcZunit.y, vtcZunit.z);

	t_vertex dest1 = vertex_init(-12.34, 23.45, -34.56);
	t_vector vtc1 = vector_init(vtx0, dest1);
	printf("x = %f, y = %f, z = %f\n", vtc1.x, vtc1.y, vtc1.z);
	t_vertex orig2 = vertex_init(23.87, -37.95, 78.34);
	t_vertex dest2 = vertex_init(-12.34, 23.45, -34.56);
	t_vector vtc2 = vector_init(orig2, dest2);
	printf("x = %f, y = %f, z = %f\n", vtc2.x, vtc2.y, vtc2.z);
	printf("Magnitude is %f\n", vector_magnitude(vtc2));

	t_vector nVtc2 = vector_normalize(vtc2);
	printf("nvtc2 = x = %f, y = %f, z = %f\n", nVtc2.x, nVtc2.y, nVtc2.z);
	printf("Magnitude is %f\n", vector_magnitude(nVtc2));
	t_vector vtcadd = vector_add(vtc1, vtc2);
	printf("addition = x = %f, y = %f, z = %f\n", vtcadd.x, vtcadd.y, vtcadd.z);
	t_vector vtcsub = vector_sub(vtc1, vtc2);
	printf("soustraction = x = %f, y = %f, z = %f\n", vtcsub.x, vtcsub.y, vtcsub.z);
	t_vector vtcopp = vector_opposite(vtc1);
	printf("oppose = x = %f, y = %f, z = %f\n", vtcopp.x, vtcopp.y, vtcopp.z);
	t_vector vtcmul = vector_mul(vtc1, 42);
	printf("mul = x = %f, y = %f, z = %f\n", vtcmul.x, vtcmul.y, vtcmul.z);
	t_vector vtcdiv = vector_div(vtc1, 42);
	printf("div = x = %f, y = %f, z = %f\n", vtcdiv.x, vtcdiv.y, vtcdiv.z);
	printf("dot product vtc1 et vtc2 = %f\n", vector_dotproduct(vtc1, vtc2));
	printf("cos de vtc1 et 2 = %f\n", vector_cos(vtc1, vtc2));
	printf("cos de vtcxunit et vtcyunit = %f\n", vector_cos(vtcXunit, vtcYunit));
	t_vector vtccross = vector_crossproduct(vtc1, vtc2);
	t_vector vtccross2 = vector_crossproduct(vtcXunit, vtcYunit);
	printf("x = %f, y = %f, z = %f\n", vtccross.x, vtccross.y, vtccross.z);
	printf("x = %f, y = %f, z = %f\n", vtccross2.x, vtccross2.y, vtccross2.z);

	printf("identity\n");
	t_matrix identity = identity_matrix_init();
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", identity.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("translation\n");
	t_matrix translation = translation_matrix_init(vector_init(vertex_init(0,0,0), vertex_init(20, 20, 0)));
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", translation.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("scale\n");
	t_matrix scale = scale_matrix_init(10);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", scale.matrix[y][x]);
		printf("\n");
	}
	printf("\n");


	printf("ROTX\n");
	t_matrix rotx = rotx_matrix_init(45);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", rotx.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("ROTY\n");
	t_matrix roty = roty_matrix_init(90);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", roty.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("ROTZ\n");
	t_matrix rotz = rotz_matrix_init(360);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", rotz.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	t_matrix multiplied = translation;

	printf("mult\n");
	multiplied = matrix_mult(matrix_mult(matrix_mult(matrix_mult(translation, rotx), roty), rotz), scale);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", multiplied.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	t_vertex vtxA = vertex_init(1, 1, 0);
	t_vertex vtcmat = matrix_mult_vertex(multiplied, vtxA);
	printf("soustraction = x = %f, y = %f, z = %f w = %f\n", vtcmat.x, vtcmat.y, vtcmat.z, vtcmat.w);
	return (0);
}

t_sphere			*sphere_malloc(t_vertex p, float rad, t_vector r, t_color c)
{
	t_sphere		*sphere;

	sphere = (t_sphere*)ft_malloc(sizeof(t_sphere));
	sphere->pos = p;
	sphere->radius = rad;
	sphere->orientation = r;
	sphere->color = c;
	sphere->next = NULL;
	return (sphere);
}

t_camera			*camera_malloc(t_vertex pos, t_vector orientation)
{
	t_camera		*camera;

	camera = (t_camera*)ft_malloc(sizeof(t_camera));
	camera->pos = pos;
	camera->orientation = orientation;
	camera->next = NULL;
	return (camera);
}

// manque la rotation en z de la cam, il faut son orientation (le vecteur) et sa rotation sur ce vecteur

t_light				*light_malloc(t_vertex pos, t_color color)
{
	t_light			*light;

	light = (t_light*)ft_malloc(sizeof(t_light));
	light->pos = pos;
	light->color = color;
	light->next = NULL;
	return (light);
}

int					parse_scene(t_env *env)
{
	t_scene			*scene;
	t_vertex		pos;
	t_vector		orientation;
	t_color			color;

	scene = (t_scene*)ft_malloc(sizeof(t_scene));
	pos = vertex_init(10, 10, 10);
	orientation = vector_init(vertex_init(0, 0, 0), vertex_init(0, 0, 1));
	color = color_init(0xff00ff);
	scene->sphere = sphere_malloc(pos, 3.0, orientation, color);
	pos = vertex_init(-10, -5, 0);
	scene->sphere->next = sphere_malloc(pos, 2.0, orientation, color);
	pos = vertex_init(20, -10, 2);
	scene->sphere->next->next = sphere_malloc(pos, 6.0, orientation, color);
	pos = vertex_init(20, 0, 10);
	color = color_init(0xffffff);
	scene->light = light_malloc(pos, color);
	pos = vertex_init(-5, 0.2, 3.6);
	scene->light->next = light_malloc(pos, color);
	env->scene = scene;
	pos = vertex_init(10, 5, 1);
	env->camera = camera_malloc(pos, orientation);
	return (1);
}

int					light_copy(t_env *env)
{
	t_light			*ptr;
	t_light			*cpyptr;

	ptr = env->scene->light;
	if (ptr)
	{
		env->scene_copy->light = light_malloc(ptr->pos, ptr->color);
		cpyptr = env->scene_copy->light;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = light_malloc(ptr->pos, ptr->color);
			cpyptr = cpyptr->next;
			ptr = ptr->next;
		}
	}
	return (1);
}

int					sphere_copy(t_env *env)
{
	t_sphere		*ptr;
	t_sphere		*cpyptr;

	ptr = env->scene->sphere;
	if (ptr)
	{
		env->scene_copy->sphere = sphere_malloc(ptr->pos, ptr->radius, ptr->orientation, ptr->color);
		cpyptr = env->scene_copy->sphere;
		ptr = ptr->next;
		while (ptr)
		{
			cpyptr->next = sphere_malloc(ptr->pos, ptr->radius, ptr->orientation, ptr->color);
			cpyptr = cpyptr->next;
			ptr = ptr->next;
		}
	}
	return (1);
}

int					scene_copy(t_env *env)
{
	env->scene_copy = (t_scene*)ft_malloc(sizeof(t_scene));
	sphere_copy(env);
	light_copy(env);
	return (1);
}

int					print_objets(t_scene *scene)
{
	t_sphere		*ptr;
	t_light			*ptr2;
	int				i;

	ptr = scene->sphere;
	i = 1;
	while (ptr)
	{
		printf("SPHERE NUMBER %d\ncenter = [%.2f][%.2f][%.2f]\nRadius = %f\norientation = [%.2f][%.2f][%.2f]\ncolor = [%d][%d][%d]\n\n", i, ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->radius, ptr->orientation.x, ptr->orientation.y, ptr->orientation.z, ptr->color.rgb.r, ptr->color.rgb.g, ptr->color.rgb.b);
		i++;
		ptr = ptr->next;
	}
	ptr2 = scene->light;
	i = 1;
	while (ptr2)
	{
		printf("LIGHT NUMBER %d\npos = [%.2f][%.2f][%.2f]\ncolor = [%d][%d][%d]\n\n", i, ptr2->pos.x, ptr2->pos.y, ptr2->pos.z, ptr2->color.rgb.r, ptr2->color.rgb.g, ptr2->color.rgb.b);
		i++;
		ptr2 = ptr2->next;
	}
	printf("\n");
	return (1);
}

int					print_camera(t_camera *cam)
{
	t_camera		*ptr;

	ptr = cam;
	while (ptr)
	{
		printf("CAMERA (actually only one)\npos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->orientation.x, ptr->orientation.y, ptr->orientation.z);
		ptr = ptr->next;
	}
	printf("\n");
	return (1);
}

int					world_to_cam(t_camera *cam, t_scene *copy)
{
	void			*ptr;
	t_matrix		matrix;

	matrix = translation_matrix_init(vector_opposite(vector_init(vertex_init(0,0,0), cam->pos)));
	ptr = copy->sphere;
	while (ptr)
	{
		((t_sphere*)ptr)->pos = matrix_mult_vertex(matrix, ((t_sphere*)ptr)->pos);
		ptr = ((t_sphere*)ptr)->next;
	}
	ptr = copy->light;
	while (ptr)
	{
		((t_light*)ptr)->pos = matrix_mult_vertex(matrix, ((t_light*)ptr)->pos);
		ptr = ((t_light*)ptr)->next;
	}
	return (1);
}

int					main(void)
{
	t_env			*env;

//	test();
	env = env_init();
	parse_scene(env);
	scene_copy(env);
	if (env->scene)
	{
		print_camera(env->camera);
		print_objets(env->scene);
		world_to_cam(env->camera, env->scene_copy);
		print_camera(env->camera);
		print_objets(env->scene_copy);
		exit(1);
	}
	raytracing(env);
	return (1);
}
