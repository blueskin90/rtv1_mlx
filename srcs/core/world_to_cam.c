/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_cam.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:54:19 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 02:35:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
int					rotation_type(t_vec a, t_vec b)
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

t_matrix			find_rotation_matrix(t_vec to_rotate, t_vec goal)
{
	t_matrix		rotxmatrix;
	t_matrix		rotymatrix;
	t_matrix		rotzmatrix;
	t_matrix		finalrotmatrix;

	
	return (finalrotmatrix);
}

dd*/
t_matrix			camrotmatrix_inverse(t_camera *cam)
{
	t_matrix		matrixrot;

	matrixrot = rotx_matrix_init(cam->rotx);
	matrixrot = matrix_mult(matrixrot, roty_matrix_init(cam->roty));
	matrixrot = matrix_mult(matrixrot, rotz_matrix_init(cam->rotz));
	return (matrixrot);
}

t_matrix			camrotmatrix(t_camera *cam)
{
	t_matrix		matrixrot;

	matrixrot = roty_matrix_init(cam->roty);
	//matrixrot = rotx_matrix_init(cam->rotx);
	//matrixrot = matrix_mult(matrixrot, roty_matrix_init(cam->roty));
	//matrixrot = matrix_mult(matrixrot, rotz_matrix_init(cam->rotz));
	return (matrixrot);
}

int					matrix_to_obj(t_matrix matrix, t_obj *original, t_obj *copy, t_camera *cam)
{
	copy->pos = matrix_mult_vec(matrix, original->pos);
	copy->rot = vec_normalize(vec_sub(matrix_mult_vec(matrix, vec_add(vec_init(cam->pos, original->pos), original->rot)), vec_init(cam->pos, original->pos)));
	return (1);
}

t_matrix	rotmatrix_axis_angle(t_vec v, float angle)
{
	t_matrix	matrix;
	float		cos;
	float		sin;

	if (isequalfloat(angle, 0.0) || isnan(angle))
		return (identity_matrix_init());
	cos = cosf(angle);
	sin = sinf(angle);
	matrix.matrix[0][0] = cos + v.x * v.x * (1 - cos);
	matrix.matrix[0][1] = v.x * v.y * (1 - cos) - v.z * sin;
	matrix.matrix[0][2] = v.x * v.z * (1 - cos) + v.y * sin;
	matrix.matrix[0][3] = 0;
	matrix.matrix[1][0] = v.y * v.x * (1 - cos) + v.z * sin;
	matrix.matrix[1][1] = cos + v.y * v.y * (1 - cos);
	matrix.matrix[1][2] = v.y * v.z * (1 - cos) - v.x * sin;
	matrix.matrix[1][3] = 0;
	matrix.matrix[2][0] = v.z * v.x * (1 - cos) - v.y * sin;
	matrix.matrix[2][1] = v.z * v.y * (1 - cos) + v.x * sin; 
	matrix.matrix[2][2] = cos + v.z * v.z * (1 - cos);
	matrix.matrix[2][3] = 0;
	matrix.matrix[3][0] = 0; 
	matrix.matrix[3][1] = 0;
	matrix.matrix[3][2] = 0;
	matrix.matrix[3][3] = 1;
	return (matrix);
}

int					isequalfloat(float a, float b)
{
	if (a < b + TOLERANCE / 2 && a > b - TOLERANCE / 2)
		return (1);
	return (0);
}

int					world_to_cam2(t_camera *cam, t_scene *scene, t_scene *copy)
{
	/*
	t_obj			*ptr;
	t_obj			*ptr2;
	t_light			*lightptr;
	t_light			*lightptr2;
	t_matrix		matrix_tran;
	t_matrix		matrix_rot;
	t_matrix		final_matrix;
	t_vec			axis;
	float			angle;

	print_vec(cam->pos);
	print_vec(cam->orientation);
	angle = vec_dotproduct(cam->orientation, vec_init0(0,0,1));
	if (isequalfloat(angle, -1))
		angle = degtorad(180);
	else
		angle = acosf(angle);
	axis = vec_norm(vec_crossproduct(cam->orientation, vec_init0(0,0,1)));
	matrix_rot = rotation_from_vec_angle(axis, angle);
	matrix_tran = translation_matrix_init(vec_opposite(cam->pos));
	final_matrix = matrix_mult(matrix_tran, matrix_rot);
	ptr = scene->objs;
	ptr2 = copy->objs;
	while (ptr)
	{
//		matrix_to_obj(final_matrix, ptr, ptr2, cam);
		ptr2->pos = matrix_mult_vec(matrix_rot, matrix_mult_vec(matrix_tran, ptr->pos));
//		ptr2->pos = matrix_mult_vec(final_matrix, ptr->pos);
//		ptr2->rot = matrix_mult_vec(matrix_rot, matrix_mult_vec(matrix_tran, ptr->rot));
		if (ptr2->type == PLANE)
		{
//			tmp = vec_init(vec_init(0,0,0), ptr->pos);
//			tmp = vec_add(tmp, ptr->params.plane.normal);
//			tmp = matrix_mult_vec(matrix_rot, tmp);
//			tmp = vec_sub(tmp, vec_init(vec_init(0,0,0), ptr->pos));
//			ptr2->params.plane.normal = tmp;
			ptr2->params.plane.normal = vec_norm(vec_init(ptr2->pos, matrix_mult_vec(matrix_rot, matrix_mult_vec(matrix_tran, ptr->params.plane.lookat))));
		}
			// deplace et rotate la position;
//		((t_sphere*)ptr2)->rot = ((t_sphere*)ptr)->orientation; 
//		if (matrix_rot)
//		{
//			print_vec(((t_sphere*)ptr)->orientation);
//			((t_sphere*)ptr)->orientation = matrix_mult_vec(*matrix_rot, ((t_sphere*)ptr)->orientation);
//			print_vec(((t_sphere*)ptr)->orientation);
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
		lightptr2->pos = matrix_mult_vec(matrix_tran, lightptr->pos);
		lightptr = lightptr->next;
		lightptr2 = lightptr2->next;
	}
	return (1);
	*/
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

	matrix_tran = translation_matrix_init(vec_opposite(vec_init(vec_init(0,0,0), cam->pos)));
	matrix_rot = camrotmatrix(cam);
	cam->orientation = matrix_mult_vec(matrix_rot, cam->orientation);
	ptr = copy->sphere;
	while (ptr)
	{
		((t_sphere*)ptr)->pos = matrix_mult_vec(matrix_tran, ((t_sphere*)ptr)->pos);
		((t_sphere*)ptr)->orientation = matrix_mult_vec(matrix_rot, ((t_sphere*)ptr)->orientation);
		ptr = ((t_sphere*)ptr)->next;
	}
	ptr = copy->light;
	while (ptr)
	{
		((t_light*)ptr)->pos = matrix_mult_vec(matrix_tran, ((t_light*)ptr)->pos);
		ptr = ((t_light*)ptr)->next;
	}
	return (1);
}*/
