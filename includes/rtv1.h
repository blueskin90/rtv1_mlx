/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/10/21 20:30:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include <math.h>

# define MALLOC_FAIL "Malloc failed\n"
# define MLX_FAIL "Couldn't start MLX\n"
# define WINDOW_FAIL "Couldn't open a new window\n"
# define MLX_IMG_FAIL "MLX couldn't get a new image\n"

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




typedef struct		s_light
{
	t_vertex		pos;
	struct s_light	*next;
}					t_light;

typedef struct		s_sphere
{
	float			radius;
	t_vertex		center;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_camera
{
	t_vertex		pos;
	t_vector		orientation;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_scene
{
	t_sphere		*sphere;
	t_light			*light;
}					t_scene;

typedef struct		s_viewplane
{
	float			width;
	float			height;
}					t_viewplane;




typedef struct		s_img
{
	int				width;
	int				height;
	void			*imgptr;
	char			*img_str;
	int				bpp;
	int				sl;
	int				endian;
}					t_img;

typedef struct		s_win
{
	int				winx;
	int				winy;
	void			*winptr;
	t_img			*img;
}					t_win;

typedef struct		s_env
{
	void			*mlx;
	t_win			*win;
}					t_env;

/*
** Raytracing functions
*/

int					raytracing(t_env *env);
int					renderer(t_scene *scene, t_camera *camera, t_img *img);
int					shootray(t_ray ray, t_scene *scene);
void				mlx_px_to_img(t_img *img, int x, int y, int color);

/*
** Env initialization and minilibx init
*/

t_env				*env_init(void);
void				ft_error(char *error);
t_win				*win_init(int width, int height, char *name, void *mlx);
t_img				*img_init(int width, int height, void *mlx);

/*
** Generic functions
*/

void				*ft_malloc(unsigned int size);
void				ft_error(char *str);

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


float				degtorad(float deg);
float				radtodeg(float rad);

#endif
