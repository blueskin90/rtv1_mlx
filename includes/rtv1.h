/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/11/19 03:30:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "libftg.h"
# include "keys.h"
# include <limits.h>

# define MALLOC_FAIL "Malloc failed\n"
# define MLX_FAIL "Couldn't start MLX\n"
# define WINDOW_FAIL "Couldn't open a new window\n"
# define MLX_IMG_FAIL "MLX couldn't get a new image\n"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define TOLERANCE 0.00001
extern float g_smallest;
extern float g_biggest;
/*
** struct of objects
*/

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
	t_vec			axis;
	float			angle;
}					t_cone;

typedef struct		s_cylinder
{
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
	struct s_obj	*obj;
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
	float			(*intersect)(t_ray, struct s_obj*);
	t_params		params;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_scene
{
	t_obj			*objs;
	t_light			*light;
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
** Event Listeners
*/
void				events_listener(t_env *env);
/*
** TO DELETE
*/
int					test(void);
/*
** STRUCTURES 
*/
int					light_copy(t_env *env);
int					sphere_copy(t_env *env);
int					scene_copy(t_env *env);
t_obj				*sphere_malloc(t_vec p, float rad, t_vec r, t_color c);
t_obj				*plane_malloc(t_vec p, t_vec lookat, t_color c);
t_camera			*camera_malloc(t_vec pos, t_vec lookat, float angle);
t_light				*light_malloc(t_vec pos, t_color color);
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
int					shootray(t_ray ray, t_scene *scene);
float				shoot_ray(t_ray ray, t_env *env, t_obj **objs);
void				mlx_px_to_img(t_img *img, int x, int y, int color);
int					colorization(t_env *env, t_ray ray, float nearest, t_obj *sphere);
/*
** INTERSECTIONS
*/
float				sphere_intersection(t_ray ray, t_obj *sphere);
float				plane_intersection(t_ray ray, t_obj *plan);
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

#endif
