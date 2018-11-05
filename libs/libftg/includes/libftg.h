/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 17:59:57 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTG_H
# define LIBFTG_H

# include <math.h>

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vertex;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vector;

typedef struct		s_ray
{
	t_vertex		origin;
	t_vector		dir;
}					t_ray;

typedef struct		s_matrix
{
	float			matrix[4][4];
}					t_matrix;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
	int				value;
}					t_rgb;

typedef struct		s_hsv
{
	int				h;
	int				s;
	int				v;
}					t_hsv;

typedef struct		s_color
{
	t_rgb			rgb;
	t_hsv			hsv;	
}					t_color;

/*
** Color functions
*/

int					hsv_to_rgb(t_hsv hsv);
t_hsv				rgb_to_hsv(int color);
void				modifyhue(int y, t_color *color);
void				modifysv(int x, int y, t_color *color);
t_rgb				int_to_rgb(int c);
int					get_rgb(unsigned char r, unsigned char g, unsigned char b);
int					rgb_to_int(t_rgb rgb);
int					get_closestcolor(t_color *color);
t_color				color_init(int color);

/*
** Generic functions
*/
float				ft_min(float a, float b, float c);
float				ft_max(float a, float b, float c);
/*
** Vector and Vertex matrix and math handling functions
*/

t_vertex			vertex_init(float x, float y, float z);

t_vector			vector_init(t_vertex a, t_vertex b);
t_vector			vector_normalize(t_vector a);
t_vector			vector_add(t_vector a, t_vector b);
t_vector			vector_sub(t_vector a, t_vector b);
t_vector			vector_mul(t_vector a, float s);
t_vector			vector_div(t_vector a, float s);
t_vector			vector_opposite(t_vector a);
t_vector			vector_crossproduct(t_vector a, t_vector b);
float				vector_dotproduct(t_vector a, t_vector b);
float				vector_magnitude(t_vector a);
float				vector_cos(t_vector a, t_vector b);

t_ray				ray_init(t_vertex origin, t_vector direction);

t_matrix			identity_matrix_init(void);
t_matrix			scale_matrix_init(float scale);
t_matrix			translation_matrix_init(t_vector tranvec);
t_matrix			rotx_matrix_init(float degrees);
t_matrix			roty_matrix_init(float degrees);
t_matrix			rotz_matrix_init(float degrees);
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vertex			matrix_mult_vertex(t_matrix a, t_vertex b);
float				degtorad(float deg);
float				radtodeg(float rad);

#endif
