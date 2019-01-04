/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:50:59 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 23:07:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix		world_to_obj_matrix(t_obj *obj)
{
	t_matrix	matrix;
	t_vec		zaxis;
	t_vec		yaxis;
	t_vec		xaxis;

	zaxis = obj->dir;
	xaxis = obj->right;
	yaxis = obj->up;
	matrix = identity_matrix_init();
	matrix.matrix[0][0] = xaxis.x;
	matrix.matrix[0][1] = xaxis.y;
	matrix.matrix[0][2] = xaxis.z;
	matrix.matrix[1][0] = yaxis.x;
	matrix.matrix[1][1] = yaxis.y;
	matrix.matrix[1][2] = yaxis.z;
	matrix.matrix[2][0] = zaxis.x;
	matrix.matrix[2][1] = zaxis.y;
	matrix.matrix[2][2] = zaxis.z;
	matrix_mult(matrix, rotmatrix_axis_angle(vec_z(), obj->roll));
	return (matrix);
}

t_matrix		obj_to_world_matrix(t_obj *obj)
{
	t_matrix	matrix;

	matrix = obj->world_to_obj;
	matrix.matrix[0][1] = obj->world_to_obj.matrix[1][0];
	matrix.matrix[0][2] = obj->world_to_obj.matrix[2][0];
	matrix.matrix[0][3] = obj->world_to_obj.matrix[3][0];
	matrix.matrix[1][0] = obj->world_to_obj.matrix[0][1];
	matrix.matrix[1][2] = obj->world_to_obj.matrix[2][1];
	matrix.matrix[1][3] = obj->world_to_obj.matrix[3][1];
	matrix.matrix[2][0] = obj->world_to_obj.matrix[0][2];
	matrix.matrix[2][1] = obj->world_to_obj.matrix[1][2];
	matrix.matrix[2][3] = obj->world_to_obj.matrix[3][2];
	matrix.matrix[3][0] = obj->world_to_obj.matrix[0][3];
	matrix.matrix[3][1] = obj->world_to_obj.matrix[1][3];
	matrix.matrix[3][2] = obj->world_to_obj.matrix[2][3];
	return (matrix);
}

t_vec			get_rightdir(t_vec dir)
{
	if (is_equal_vec(dir, vec_y()))
		return (vec_x());
	else if (is_equal_vec(dir, vec_opposite(vec_y())))
		return (vec_x());
	return (vec_normalize(vec_opposite(vec_crossproduct(dir, vec_y()))));
}

t_vec			get_updir(t_vec dir, t_vec right)
{
	return (vec_norm(vec_crossproduct(dir, right)));
}
