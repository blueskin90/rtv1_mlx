/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 18:03:26 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTG_H
# define LIBFTG_H

# include <math.h>

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
	float			w;
}				t_vec;

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

typedef struct		s_hsl
{
	float			h;
	float			s;
	float			l;
}					t_hsl;

typedef struct		s_hsv
{
	int				h;
	int				s;
	int				v;
}					t_hsv;

typedef	union				
{
	t_hsv			hsv;
	t_hsl			hsl;
// verifier norme
}					u_color_type;
typedef struct		s_color
{
	t_rgb			rgb;
	//t_hsv			hsv;	
	u_color_type	type;
}					t_color;

/*
** Color functions
*/

int					hsv_to_rgb(t_hsv hsv);
int					hsl_to_rgb(t_hsl hsl);
t_hsv				rgb_to_hsv(int color);
t_hsl				rgb_to_hsl(int color);
void				modifyhue_hsv(int y, t_color *color);
void				modifyhue_hsl(int y, t_color *color);
void				modifysv(int x, int y, t_color *color);
void				modifyhsl(int x, int y, t_color *color);
t_rgb				int_to_rgb(int c);
int					get_rgb(unsigned char r, unsigned char g, unsigned char b);
int					rgb_to_int(t_rgb rgb);
int					get_closestcolor_hsv(t_color *color);
int					get_closestcolor_hsl(t_color *color);
t_color				color_init_hsv(int color);
t_color				color_init_hsl(int color);
void				change_hsl(t_color	*color, float h, float s, float l);

/*
** Generic functions
*/
float				ft_min(float a, float b, float c);
float				ft_max(float a, float b, float c);
/*
** Vector and Vertex matrix and math handling functions
*/

t_vec			vec_init(t_vec a, t_vec b);
t_vec			vec_init0(float x, float y, float z);
t_vec			vec_normalize(t_vec a);
t_vec			vec_norm(t_vec a);
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_sub(t_vec a, t_vec b);
t_vec			vec_mul(t_vec a, float s);
t_vec			vec_div(t_vec a, float s);
t_vec			vec_opposite(t_vec a);
t_vec			vec_crossproduct(t_vec a, t_vec b);
float				vec_dotproduct(t_vec a, t_vec b);
float				vec_dot(t_vec a, t_vec b);
float				vec_magnitude(t_vec a);
float				vec_cos(t_vec a, t_vec b);
t_matrix			identity_matrix_init(void);
t_matrix			scale_matrix_init(float scale);
t_matrix			translation_matrix_init(t_vec tranvec);
t_matrix			rotx_matrix_init(float degrees);
t_matrix			roty_matrix_init(float degrees);
t_matrix			rotz_matrix_init(float degrees);
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vec				matrix_mult_vec(t_matrix a, t_vec b);
float				degtorad(float deg);
float				radtodeg(float rad);
float				min_of_vec(t_vec vec);
float				max_of_vec(t_vec vec);
int					vec_is_0(t_vec vec);
#endif
