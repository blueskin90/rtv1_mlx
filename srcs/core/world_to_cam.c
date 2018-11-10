/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:54:19 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/10 21:21:42 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int					rotation_type(t_vector a, t_vector b)
{
	char			flags;
	t_vector		tmp;

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

t_matrix			*camrotmatrix(t_camera *cam)
{
//	t_vector		v;
//	float			s;
//	float			c;
	t_vector		comparaison;
	t_matrix		*matrixrot;
	int				rot_type;

//	v = vector_crossproduct(cam->orientation, orientation); 
//	s = vector_magnitude(v);
//	c = vector_dotproduct(cam->orientation, orientation);
	printf("cam->orientation :");
	print_vector(cam->orientation);
	printf("comparaison :");
	comparaison = vector_init(vertex_init(0,0,0), vertex_init(0,0,1));
	print_vector(comparaison);
	rot_type = rotation_type(cam->orientation, comparaison);
	if (rot_type == 0)
	{
		printf("same direction\n");
		matrixrot = NULL;
	}
	else
	{
		matrixrot = (t_matrix*)ft_malloc(sizeof(t_matrix));
		if (rot_type == 1)
		{
				printf("opposite direction\n");
			*matrixrot = scale_matrix_init(-1);
		}
		else
		{
//			*matrixrot = find_rotation_matrix(cam->orientation, comparaison);
			printf("other\n");
		}
	}
	/*
	if (ft_memcmp(&cam->orientation, &comparaison, sizeof(t_vector)) == 0)
	{
		printf("Same direction !\n");
		return (NULL);
	}
	printf("cam->orientation :");
	print_vector(cam->orientation);
	comparaison = vector_opposite(comparaison);
	printf("comparaison :");
	print_vector(comparaison);
	if (ft_memcmp(&(cam->orientation), &comparaison, sizeof(t_vector)) == 0)
	{
		printf("Opposite !\n");
		matrixrot = (t_matrix*)ft_malloc(sizeof(t_matrix));
		*matrixrot = scale_matrix_init(-1);
		return (matrixrot);
	}
	else
		printf("[%f][%f][%f]\n",comparaison.x, comparaison.y, comparaison.z);
		*/
	return (NULL);
}

int					world_to_cam2(t_camera *cam, t_scene *scene, t_scene *copy)
{
	void			*ptr;
	void			*ptr2;
	t_matrix		matrix_tran;
//	t_matrix		*matrix_rot;
//	t_matrix		matrix_rotx;
//	t_matrix		matrix_roty;
//	t_matrix		matrix_rotz;

	matrix_tran = translation_matrix_init(vector_opposite(vector_init(vertex_init(0, 0, 0), cam->pos)));
//	matrix_rot = camrotmatrix(cam);
	ptr = scene->sphere;
	ptr2 = copy->sphere;
	while (ptr)
	{
		((t_sphere*)ptr2)->pos = matrix_mult_vertex(matrix_tran, ((t_sphere*)ptr)->pos);
//		if (matrix_rot)
//		{
//			print_vector(((t_sphere*)ptr)->orientation);
//			((t_sphere*)ptr)->orientation = matrix_mult_vector(*matrix_rot, ((t_sphere*)ptr)->orientation);
//			print_vector(((t_sphere*)ptr)->orientation);
//		}
//		else
//			printf("matrice nulle !\n");
		ptr = ((t_sphere*)ptr)->next;
		ptr2 = ((t_sphere*)ptr2)->next;
	}
	ptr = scene->light;
	ptr2 = copy->light;
	while (ptr)
	{
		((t_light*)ptr2)->pos = matrix_mult_vertex(matrix_tran, ((t_light*)ptr)->pos);
		ptr = ((t_light*)ptr)->next;
		ptr2 = ((t_light*)ptr2)->next;
	}
	return (1);

}

int					world_to_cam(t_camera *cam, t_scene *copy)
{
	void			*ptr;
	t_matrix		matrix_tran;
	t_matrix		*matrix_rot;
//	t_matrix		matrix_rotx;
//	t_matrix		matrix_roty;
//	t_matrix		matrix_rotz;

	matrix_tran = translation_matrix_init(vector_opposite(vector_init(vertex_init(0,0,0), cam->pos)));
	matrix_rot = camrotmatrix(cam);
	ptr = copy->sphere;
	while (ptr)
	{
		((t_sphere*)ptr)->pos = matrix_mult_vertex(matrix_tran, ((t_sphere*)ptr)->pos);
		if (matrix_rot)
		{
			print_vector(((t_sphere*)ptr)->orientation);
			((t_sphere*)ptr)->orientation = matrix_mult_vector(*matrix_rot, ((t_sphere*)ptr)->orientation);
			print_vector(((t_sphere*)ptr)->orientation);
		}
		else
			printf("matrice nulle !\n");
		ptr = ((t_sphere*)ptr)->next;
	}
	ptr = copy->light;
	while (ptr)
	{
		((t_light*)ptr)->pos = matrix_mult_vertex(matrix_tran, ((t_light*)ptr)->pos);
		ptr = ((t_light*)ptr)->next;
	}
	return (1);
}
