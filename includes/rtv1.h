/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 07:14:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "libftg.h"
# include "fail_errors.h"
# include "keys.h"
# include <limits.h>
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TOLERANCE 0.01

# define OBJ_HIT_MODE 0
# define OBJ_HIT_LENGTH_MODE 1
# define RAY_COLOR_MODE 2
# define MODE_MAX 2

# include <stdio.h> // a suppr apres !

/*
 *
 * go retaper a partir de colorize (et certaines fonctions d'intersection)
 *
 *
*/

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
	t_color			color;
	t_vec			normal;
	t_vec			hit_pos;
	float			length;
	struct s_obj	*obj_hit;
}					t_ray;

typedef struct		s_obj
{
	t_vec			pos;
	t_vec			dir;
	t_vec			up;
	t_color			color;
	t_matrix		world_to_obj;
	t_matrix		obj_to_world;
	
	float			(*intersect)(t_ray, struct s_obj*);
	t_type			type;
	t_params		params;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_scene
{
	t_obj			*objs;
	t_obj			*lights;
	t_obj			*cameras;
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

/*
** IN TESTING
*/

t_ray				ray_to_obj(t_ray ray, t_obj *obj);
t_ray				ray_init(t_vec pos, t_vec dir);

void				shoot_ray(t_ray *ray);
void				get_normal(t_ray *ray);
int					is_equal_float(float a, float b);
int					is_equal_vec(t_vec a, t_vec b);
int					is_opposite_vec(t_vec a, t_vec b);
float				sphere_radius(t_obj *sphere);

float				get_ratio(t_vec hit_pos, t_vec normal);
float				get_ambiant(t_ray *ray);
float				get_diffuse(t_ray *ray, t_scene *scene);
float				get_speculat(t_ray *ray, t_scene *scene, t_camera *cam);
t_ray				reflect_ray(t_ray *ray);
int					colorization(t_ray *ray, t_env *env);

/*
** INIT FUNCTIONS
*/

t_env				*env_init(void);
t_win				*win_init(int width, int height, char *name, void *mlx);
t_img				*img_init(int width, int height, void *mlx);

/*
** BASIC UTILS FUNCTIONS
*/

void				*ft_malloc(size_t size);
void				ft_error(char *str);

/*
** SINGLETON FUNCTIONS
*/

t_env				*env_get(void);
void				env_set(t_env *env);
t_scene				*scene_get(void);
void				scene_set(t_scene *scene);
t_obj				*camera_get(void);
void				camera_set(t_obj *cam);
t_ray				*renderer_get();
t_ray				*renderer_getray(int nb);
int					renderer_getraymax();
void				renderer_set();
t_win				*win_get(void);
int					win_getx(void);
int					win_gety(void);
void				*mlx_get(void);
int					print_mode_get(void);
void				print_mode_set(int mode);
int					cursor_getx(void);
int					cursor_gety(void);
void				cursor_movex(int x);
void				cursor_movey(int y);
void				cursor_reset(void);
int					cursor_mode_get(void);
void				cursor_mode_toggle(void);
void				cursor_mode_set(int value);
/*
** OBJET MALLOC
*/

t_obj				*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_color c);
t_obj				*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_color c);
void				obj_sphere_params(t_obj *obj, float radius);
void				obj_cylinder_params(t_obj *obj, float radius);
void				obj_cone_params(t_obj *obj, float angle);
void				obj_plane_params(t_obj *obj);
void				obj_camera_params(t_obj *obj, float fov);
void				obj_light_params(t_obj *obj, float intensity);
void				renderer_malloc(t_obj *camera);

/*
** RAYTRACING FUNCTIONS
*/

void				raytracing(void);
void				raytracing_lights(void);
void				shoot_ray(t_ray *ray);
void				get_normal(t_ray *ray);
void				printing(void);

/*
** INTERSECTION FUNCTIONS
*/

float				plane_intersection(t_ray ray, t_obj *plane);
float				cone_intersection(t_ray ray, t_obj *cone);
float				cylinder_intersection(t_ray ray, t_obj *cylinder);
float				sphere_intersection(t_ray ray, t_obj *sphere);

/*
** EVENT LISTENER
*/

void				events_listener(t_env *env);
int					key_pressed(int key);
int					mouse_move(int x, int y);

/*
** MATRIX FUNCTIONS
*/

t_matrix			rotmatrix_axis_angle(t_vec v, float angle);
t_matrix			world_to_obj_matrix(t_obj *obj);
t_matrix			obj_to_world_matrix(t_obj *obj);

/*
** CONVENIENT FUNCTIONS
*/

t_vec				vec_x(void);
t_vec				vec_y(void);
t_vec				vec_z(void);

/*
** MLX FUNCTIONS
*/

void				mlx_px_to_img(t_img *img, int x, int y, int color);

/*
** PRINTING FUNCTIONS
*/

float				get_max_raylen(void);// kinda accessoire mais utile qu'ici.
void				printing(void);
void				print_cursor_over_image(void);
void				print_final_ray_color_mode(void);
void				print_obj_hit_color_length_mode(void);
void				print_obj_hit_color_mode(void);

/* 
** DEBUG FUNCTIONS
*/

void				print_to_light_infos(t_ray *ray);
void				print_obj_hit_infos(t_ray *ray);
void				display_cursor_infos(void);
void				print_angles(void);
void				print_matrix(t_matrix matrix);
void				print_vec(t_vec v);
void				print_objects(t_scene *scene);
void				print_lights(t_scene *scene);
void				print_cameras(t_scene *scene);
void				print_scene(t_scene *scene);
void				print_renderer(t_ray *ray);
void				print_ray(t_ray *ray);
#endif
