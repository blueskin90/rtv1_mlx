/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:54:19 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/11 23:45:48 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
int					rotation_type(t_vector a, t_vector b)
{
	char			flags;

	flags = 0;
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (0); // same direction
	if (a.x == b.x && a.x == 0.0)
		flags &= 0b1;
	if (a.y == b.y && a.y == 0.0)
		flags &= 0b10;
	if (a.z == b.z && a.z == 0.0)
		flags &= 0b100;
	if (((flags ^ 0b11) == 0 && a.z == -b.z) || ((flags ^ 0b101) == 0 && a.y == -b.y)
			|| ((flags ^ 0b110) == 0 && a.x == -b.x)
			|| (a.x == -b.x && a.y == -b.y && a.z == -b.z))
		return (1); // opposite direction
	return (2); // other rotation
}

t_matrix			find_rotation_matrix(t_vector to_rotate, t_vector goal)
{
	t_matrix		rotxmatrix;
	t_matrix		rotymatrix;
	t_matrix		rotzmatrix;
	t_matrix		finalrotmatrix;

	
	return (finalrotmatrix);
}

dd*/
t_matrix			camrotmatrix(t_camera *cam)
{
	t_matrix		matrixrot;

	matrixrot = rotx_matrix_init(cam->rotx);
	matrixrot = matrix_mult(matrixrot, roty_matrix_init(cam->roty));
	matrixrot = matrix_mult(matrixrot, rotz_matrix_init(cam->rotz));
	return (matrixrot);
}

int					matrix_to_obj(t_matrix matrix, t_obj *original, t_obj *copy, t_camera *cam)
{
	copy->pos = matrix_mult_vertex(matrix, original->pos);
	copy->rot = vector_normalize(vector_sub(matrix_mult_vector(matrix, vector_add(vector_init(cam->pos, original->pos), original->rot)), vector_init(cam->pos, original->pos)));
	return (1);
}

int					world_to_cam2(t_camera *cam, t_scene *scene, t_scene *copy)
{
	t_obj			*ptr;
	t_obj			*ptr2;
	t_light			*lightptr;
	t_light			*lightptr2;
	t_matrix		matrix_tran;
	t_matrix		matrix_rot;
	t_matrix		final_matrix;

	matrix_tran = translation_matrix_init(vector_opposite(vector_init(vertex_init(0, 0, 0), cam->pos)));
	matrix_rot = camrotmatrix(cam);
	final_matrix = matrix_mult(matrix_tran, matrix_rot);
	ptr = scene->objs;
	ptr2 = copy->objs;
	while (ptr)
	{
		matrix_to_obj(final_matrix, ptr, ptr2, cam);
		ptr2->pos = matrix_mult_vertex(matrix_rot, matrix_mult_vertex(matrix_tran, ptr->pos));
		ptr2->rot = matrix_mult_vector(matrix_rot, matrix_mult_vector(matrix_tran, ptr->rot));
		if (ptr2->type == PLANE)
			ptr2->params.plane.normale = matrix_mult_vector(matrix_rot, matrix_mult_vector(matrix_tran, ptr->params.plane.normale));
			// deplace et rotate la position;
//		((t_sphere*)ptr2)->rot = ((t_sphere*)ptr)->orientation; 
//		if (matrix_rot)
//		{
//			print_vector(((t_sphere*)ptr)->orientation);
//			((t_sphere*)ptr)->orientation = matrix_mult_vector(*matrix_rot, ((t_sphere*)ptr)->orientation);
//			print_vector(((t_sphere*)ptr)->orientation);
//		}
//		else
//			printf("matrice nulle !\n");
		ptr = ptr->next;
		ptr2 = ptr2->next;
	}
	lightptr = scene->light;
	lightptr2 = copy->light;
	while (lightptr)
	{
		lightptr2->pos = matrix_mult_vertex(matrix_tran, lightptr->pos);
		lightptr = lightptr->next;
		lightptr2 = lightptr2->next;
	}
	return (1);

}
/*
int					world_to_cam(t_camera *cam, t_scene *copy)
{
	void			*ptr;
	t_matrix		matrix_tran;
	t_matrix		matrix_rot;
//	t_matrix		matrix_rotx;
//	t_matrix		matrix_roty;
//	t_matrix		matrix_rotz;

	matrix_tran = translation_matrix_init(vector_opposite(vector_init(vertex_init(0,0,0), cam->pos)));
	matrix_rot = camrotmatrix(cam);
	cam->orientation = matrix_mult_vector(matrix_rot, cam->orientation);
	ptr = copy->sphere;
	while (ptr)
	{
		((t_sphere*)ptr)->pos = matrix_mult_vertex(matrix_tran, ((t_sphere*)ptr)->pos);
		((t_sphere*)ptr)->orientation = matrix_mult_vector(matrix_rot, ((t_sphere*)ptr)->orientation);
		ptr = ((t_sphere*)ptr)->next;
	}
	ptr = copy->light;
	while (ptr)
	{
		((t_light*)ptr)->pos = matrix_mult_vertex(matrix_tran, ((t_light*)ptr)->pos);
		ptr = ((t_light*)ptr)->next;
	}
	return (1);
}*/
