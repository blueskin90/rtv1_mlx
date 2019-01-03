/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init_rot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:07:45 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:08:10 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

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
