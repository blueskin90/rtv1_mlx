/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:55:41 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 03:14:51 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_STRUCT_H
# define RTV1_STRUCT_H

# include "libftg.h"

typedef struct		s_RGB
{
	float			r;
	float			g;
	float			b;
	int				value;
}					t_RGB;

typedef enum		e_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
	LIGHT,
	CAMERA,
}					t_type;

typedef struct		s_sphere
{
	float			radius;
}					t_sphere;

typedef struct		s_plane
{
	int				a;
}					t_plane;

typedef struct		s_cone
{
	float			angle;
}					t_cone;

typedef struct		s_cylinder
{
	float			radius;
}					t_cylinder;

typedef struct		s_camera
{
	float			fov;
	struct s_ray	*rays;
	int				raynumber;
}					t_camera;

typedef struct		s_light
{
	float			intensity;
}					t_light;

typedef union		u_params
{
	t_sphere		sphere;
	t_plane			plane;
	t_cone			cone;
	t_cylinder		cylinder;
	t_camera		camera;
	t_light			light;
}					t_params;

typedef struct		s_ray
{
	t_vec			pos;
	t_vec			dir;
	t_vec			lookat;
	t_RGB			color;
	t_vec			normal;
	t_vec			hit_pos;
	float			length;
	struct s_obj	*obj_hit;
}					t_ray;

typedef struct		s_parse_obj
{
	t_vec			specular;	
	t_vec			diffuse;
	t_vec			position;
	t_vec			direction;
	t_vec			lookat;
	t_vec			translation;
	t_vec			rotation;
	t_vec			up;
	t_vec			right;
	float			brillance;
	float			ambiant;
	float			roll;
	t_RGB			color;
	t_type			type;
	t_params		params;
}					t_parse_obj;

typedef struct		s_obj
{
	t_vec			pos;
	t_vec			lookat;
	t_vec			dir;
	t_vec			up;
	t_vec			right;
	float			roll;
	t_RGB			color;
	t_RGB			specular;
	t_RGB			diffuse;
	float			ambiant;
	float			brillance;
	t_matrix		world_to_obj;
	t_matrix		obj_to_world;

	float			(*intersect)(t_ray, struct s_obj*);
	t_type			type;
	t_params		params;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_scene
{
	char			*name;
	t_obj			*objs;
	t_obj			*lights;
	t_obj			*cameras;
	struct s_scene	*next;
}					t_scene;

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
	t_scene			*scene;
}					t_env;

typedef struct		s_args
{
	int				parse_mode;
	int				verbose_mode;
	int				renderer_mode;
	int				print_mode;
	int				debug_mode;
	char			**files;
}					t_args;

typedef enum		e_renderer_mode
{
	NO_RENDERER,
	STACK,
	MALLOC,
	MULTITHREAD,
	GRAPHIQUE,
	CLUSTERING,
	MAX_RENDERER_MODE = 3,
}					t_renderer_mode;

typedef enum		e_parse_mode
{
	STANDARD,
	JSON,
}					t_parse_mode;

typedef enum		e_verbose_mode
{
	NO_VERBOSE,
	ARGS_PARSING,
	INIT,
	PARSING,
	SETTINGS,
	RUNNING,
	ALL_VERBOSE,
	MAX_VERBOSE_MODE,
}					t_verbose_mode;

typedef enum		e_print_mode
{
	NO_PRINT,
	HIT_COLOR,
	DEPTH_COLOR,
	TOTAL_COLOR,
	TEST_COLOR,
	MAX_PRINT_MODE,
}					t_print_mode;

#endif
