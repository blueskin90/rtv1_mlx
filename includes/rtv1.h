/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/10/15 06:07:22 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
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

/*
** Vector and Vertex handling functions
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

#endif
