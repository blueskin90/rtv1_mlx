/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/12/04 18:19:29 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "libftg.h"
# include "json_parser.h"
# include "keys.h"
# include <limits.h>
# include "mlx_errors.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TOLERANCE 0.001
/*
** struct of objects
*/

# include <stdio.h> // a suppr apres !

typedef struct		s_camera
{
	t_vec			pos;
	t_vec			lookat;
	t_vec			orientation;
	t_vec			top;
	t_vec			right;
	float			rotx;
	float			roty;
	float			rotz;
	float			fov;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_viewplane
{
	float			width;
	float			height;
}					t_viewplane;

typedef struct		s_light
{
	t_vec			pos;
	t_color			color;
	float			intensity;
	struct s_light	*next;
}					t_light;
/*
** End of struct object
*/
typedef enum		e_type
{
	SPHERE,
	PLANE,
	CONE,
	CYLINDER,
}					t_type;

typedef struct		s_spheree
{
	float			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_vec			lookat;
	t_vec			normal;
}					t_plane;

typedef struct		s_cone
{
	t_vec			lookat;
	t_vec			axis;
	float			angle;
}					t_cone;

typedef struct		s_cylinder
{
	t_vec			lookat;
	t_vec			axis;
	float			radius;
}					t_cylinder;

typedef union		u_params
{
	t_sphere		sphere;
	t_plane			plane;
	t_cone			cone;
	t_cylinder		cylinder;
}					t_params;

typedef struct		s_ray
{
	t_vec			origin;
	t_vec			direction;
	t_color			color;
	t_vec			normal;
	t_vec			hit_pos;
	float			length;
	struct s_obj	*obj_hit;
}					t_ray;

typedef struct		s_obj
{
	t_vec			pos;
	t_vec			rot;
	float			rotx;
	float			roty;
	float			rotz;
	t_vec			xworld;
	t_vec			yworld;
	t_vec			zworld;
	t_color			color;
	t_type			type;
	t_matrix		world_to_obj;
	float			world_to_obj_angle;
	t_vec			world_to_obj_vec;
	t_matrix		obj_to_world;
	float			obj_to_world_angle;
	t_vec			obj_to_world_vec;

	float			(*intersect)(t_ray, struct s_obj*);
	t_params		params;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_scene
{
	t_obj			*objs;
	t_light			*light;
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
	t_scene			*scene_copy;
	t_camera		*camera;
}					t_env;

typedef struct		s_key
{
	char			*name;
	e_type			type;
	bool			required;
	u_value			defaulty;
	struct s_key	*child;
	struct s_key	*next;
}					t_key;
/*
** TMP
*/

t_vec				vec_initO_ver(t_vec a);
t_matrix			camrotmatrix(t_camera *cam);
int					is_equal_float(float a, float b);
int					is_equal_vector(t_vec a, t_vec b);
int					is_opposite_vector(t_vec a, t_vec b);
t_matrix			rotmatrix_axis_angle(t_vec axis, float angle);
int					isequalfloat(float a, float b);
/*
** PARSING
*/
t_env				*rtv1_parsing(t_elem *elem, t_env *env);
t_key				*new_key(char *name, e_type type, bool required, void *defaulty);
t_elem				*default_vector_values();
t_elem				*default_vector_object(char *name);
t_key				*basic_object_keys(char *name);
t_key				*basic_vector_keys();


/*
** Event Listeners
*/
void				events_listener(t_env *env);
/*
** TO DELETE
*/
void				print_keys(t_key *key, int padding);
void				show_one_key(t_key *elem, int padding);
int					test(void);
/*
** STRUCTURES 
*/
int					light_copy(t_env *env);
int					sphere_copy(t_env *env);
int					scene_copy(t_env *env);
t_obj				*cone_malloc(t_vec p, float angle, t_vec r, t_color c);
t_obj				*sphere_malloc(t_vec p, float rad, t_vec r, t_color c);
t_obj				*plane_malloc(t_vec p, t_vec lookat, t_color c);
t_obj				*cylinder_malloc(t_vec p, float rad, t_vec lookat, t_color c);
t_camera			*camera_malloc(t_vec pos, t_vec lookat, float angle);
t_light				*light_malloc(t_vec pos, t_color color, float intensity);
t_ray				ray_init(t_vec origin, t_vec pos);
/*
** Print functions
*/
void				print_matrix(t_matrix m);
int					print_objets(t_scene *scene);
int					print_camera(t_camera *cam);
int					print_vec(t_vec v);

/*
** Camera rotation and translation 
*/
int					rotation_type(t_vec a, t_vec b);
t_matrix			camrotmatrix(t_camera *cam);
int					world_to_cam(t_camera *cam, t_scene *copy);
int					world_to_cam2(t_camera *cam, t_scene *scene, t_scene *copy);

/*
** Raytracing functions
*/

int					raytracing(t_env *env);
int					renderer(t_scene *scene, t_camera *camera, t_img *img);
int					shoot_ray(t_ray *ray, t_scene *scene);
void				mlx_px_to_img(t_img *img, int x, int y, int color);
//int					colorization(t_env *env, t_ray ray, float nearest, t_obj *obj_hit);
int					colorization(t_ray *ray, t_env *env);
t_ray				reflect_ray(t_ray *ray);

/*
** INTERSECTIONS
*/
float				sphere_intersection(t_ray ray, t_obj *sphere);
float				plane_intersection(t_ray ray, t_obj *plan);
float				cylinder_intersection(t_ray ray, t_obj *cylinder);
float				cone_intersection(t_ray ray, t_obj *cone);
/*
** Env initialization and minilibx init
*/

t_env				*env_init(void);
void				ft_error(char *error);
t_win				*win_init(int width, int height, char *name, void *mlx);
t_img				*img_init(int width, int height, void *mlx);


#endif
