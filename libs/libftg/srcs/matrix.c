/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 06:24:52 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 18:09:21 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

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
	//	t_matrix	projectionmatrix;
	/*s = 1.0 / (tan(ft_to_radians(p->fov) * 0.5));
	t->x[0] = s / p->ratio;
	t->x[1] = 0;
	t->x[2] = 0;
	t->x[3] = 0;
	t->y[0] = 0;
	t->y[1] = s;
	t->y[2] = 0;
	t->y[3] = 0;
	t->z[0] = 0;
	t->z[1] = 0;
	t->z[2] = -1 * (-p->near - p->far) / (p->near - p->far);
	t->z[3] = (2 * p->near * p->far) / (p->near - p->far);
	t->w[0] = 0;
	t->w[1] = 0;
	t->w[2] = -1;
	t->w[3] = 0;*/
	(void) fov;
	(void) ratio;
	(void) near;
	(void) far;
	return (identity_matrix_init());
}

t_matrix		matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			x;
	int			y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			c.matrix[y][x] = a.matrix[y][0] * b.matrix[0][x]+ a.matrix[y][1] * b.matrix[1][x]+ a.matrix[y][2] * b.matrix[2][x] + a.matrix[y][3] * b.matrix[3][x];
			x++;
		}
		y++;
	}
	return (c);
}

t_vertex		matrix_mult_vertex(t_matrix a, t_vertex b)
{
	t_vertex	c;

	c.x = a.matrix[0][0] * b.x+ a.matrix[0][1] * b.y + a.matrix[0][2] * b.z + a.matrix[0][3] * b.w;
	c.y = a.matrix[1][0] * b.x + a.matrix[1][1] * b.y + a.matrix[1][2] * b.z + a.matrix[1][3] * b.w;
	c.z = a.matrix[2][0] * b.x+ a.matrix[2][1] * b.y + a.matrix[2][2] * b.z + a.matrix[2][3] * b.w;
	c.w = a.matrix[3][0] * b.x+ a.matrix[3][1] * b.y + a.matrix[3][2] * b.z + a.matrix[3][3] * b.w;
	return (c);
}
