/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 06:24:52 by toliver           #+#    #+#             */
/*   Updated: 2018/10/15 09:24:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix		identity_matrix_init(void)
{
	t_matrix	id;

	id.matrix[0][0] = 1.0;
	id.matrix[0][1] = 0.0;
	id.matrix[0][2] = 0.0;
	id.matrix[0][3] = 0.0;
	id.matrix[1][0] = 0.0;
	id.matrix[1][1] = 1.0;
	id.matrix[1][2] = 0.0;
	id.matrix[1][3] = 0.0;
	id.matrix[2][0] = 0.0;
	id.matrix[2][1] = 0.0;
	id.matrix[2][2] = 1.0;
	id.matrix[2][3] = 0.0;
	id.matrix[3][0] = 0.0;
	id.matrix[3][1] = 0.0;
	id.matrix[3][2] = 0.0;
	id.matrix[3][3] = 1.0;
	return (id);
}

t_matrix		scale_matrix_init(float scale)
{
	t_matrix	scalematrix;

	scalematrix = identity_matrix_init();
	scalematrix.matrix[0][0] *= scale;
	scalematrix.matrix[1][1] *= scale;
	scalematrix.matrix[2][2] *= scale;
	return (scalematrix);
}

t_matrix		translation_matrix_init(t_vector tranvec)
{
	t_matrix	translationmatrix;

	translationmatrix = identity_matrix_init();
	translationmatrix.matrix[0][3] = tranvec.x;
	translationmatrix.matrix[1][3] = tranvec.y;
	translationmatrix.matrix[2][3] = tranvec.z;
	return (translationmatrix);
}

t_matrix		rotx_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[1][1] = cos;
	rotationmatrix.matrix[1][2] = -sin;
	rotationmatrix.matrix[2][1] = sin;
	rotationmatrix.matrix[2][2] = cos;
	return (rotationmatrix);
}

t_matrix		roty_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[0][0] = cos;
	rotationmatrix.matrix[0][2] = sin;
	rotationmatrix.matrix[2][0] = -sin;
	rotationmatrix.matrix[2][2] = cos;
	return (rotationmatrix);
}

t_matrix		rotz_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[0][0] = cos;
	rotationmatrix.matrix[0][1] = -sin;
	rotationmatrix.matrix[1][0] = sin;
	rotationmatrix.matrix[1][1] = cos;
	return (rotationmatrix);
}

t_matrix		projection_matrix_init(float fov, float ratio, float near, float far)
{
	t_matrix	projectionmatrix;
	
	return (projectionmatrix);
}
