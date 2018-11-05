/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmatrice.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:03:53 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/03 18:24:30 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATRICE_H
# define LIBMATRICE_H
# include <math.h>
# include <stdio.h>
# include "../../libft/includes/libft.h"

/*
**	fov -> degree
**	ratio -> double
**	near -> double
** far -> far
*/

typedef struct		s_proj
{
	double			fov;
	double			ratio;
	double			near;
	double			far;
}					t_proj;

typedef struct		s_vertex
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vertex;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	double			w;
	t_vertex		*d;
	t_vertex		*o;
}					t_vector;

typedef struct		s_matrix
{
	double				x[4];
	double				y[4];
	double				z[4];
	double				w[4];
}					t_matrix;

typedef struct	s_cam
{
	double		fov;
	double		angle;
	double		ratio_x;
	double		ratio_y;
	t_vertex	pt;
}				t_cam;

static t_vertex null_vertex = {0.0, 0.0, 0.0, 1.0};
/*
**	MATRIX
*/
t_matrix		*create_matrix(void);
t_matrix		*init_scale(double scale, t_matrix *t);
t_matrix		*init_translation(double x, double y, double z, t_matrix *t);
t_matrix		*init_x_rotation(double x_angle, t_matrix *t);
t_matrix		*init_y_rotation(double y_angle, t_matrix *t);
t_matrix		*init_z_rotation(double z_angle, t_matrix *t);
t_matrix		*init_projection(t_proj *p, t_matrix *t);
t_proj			*create_projection_struct(double fov, double ratio, double near, double far);
/*
** VERTEX
*/
t_vertex		*create_vertex(int x, int y, int z);
t_vertex		*init_vertex(int x, int y, int z, t_vertex *v);
/*
**	VECTOR
*/
t_vector		*create_vector(t_vertex *dest, t_vertex *origin);
t_vector		*init_vector(t_vector *vec, t_vertex *dest, t_vertex *origin);
double			magnitude_vector(t_vector *vec);
void			normalize_vector(t_vector *vec);
t_vector		*opposite_vector(t_vector *vec1);
t_vector		*add_vectors(t_vector *vec1, t_vector *vec2);
t_vector		*sub_vectors(t_vector *vec1, t_vector *vec2);
t_vector		*crossproduct_vectors(t_vector *vec1, t_vector *vec2);
t_vector		*scalarproduct_vector(t_vector *vec1, double sc);
double			dotproduct_vectors(t_vector *vec1, t_vector *vec2);
double			cos_vectors(t_vector *vec1, t_vector *vec2);
/*
** OPPERATIONS
*/
void			matrix_multiplication(t_matrix *t, t_vertex *point);
/*
**	SHOW FUNCTIONS
*/
void			show_matrix(t_matrix *t);
void			show_vertex(t_vertex *v);
void			show_vector(t_vector *vec);
#endif
