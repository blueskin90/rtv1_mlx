/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/11/18 15:01:08 by cvermand         ###   ########.fr       */
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

/*
** struct of objects
*/
/*typedef struct		s_ray
{
	t_vertex		origin;
	t_vector		direction;
}					t_ray;
*/
typedef struct		s_camera
{
	t_vertex		pos;
	t_vector		orientation;
	t_vector		top;
	t_vector		right;
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
	t_vertex		pos;
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
	t_vector		normal;
}					t_plane;

typedef struct		s_cone
{
	t_vector		axis;
	float			angle;
}					t_cone;

typedef struct		s_cylinder
{
	t_vector		axis;
	float			radius;
}					t_cylinder;

typedef union		u_params
{
	t_sphere		sphere;
	t_plane			plane;
	t_cone			cone;
	t_cylinder		cylinder;
}					t_params;

typedef struct		s_obj
{
	t_vertex		pos;
	t_vector		rot;
	float			rotx;
	float			roty;
	float			rotz;
	t_vector		xworld;
	t_vector		yworld;
	t_vector		zworld;
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

t_vector			vec_initO_ver(t_vertex a);
t_matrix			camrotmatrix(t_camera *cam);
int					is_equal_float(float a, float b);
int					is_equal_vector(t_vector a, t_vector b);
int					is_opposite_vector(t_vector a, t_vector b);


/*
** Event Listeners
*/
void		events_listener(t_env *env);
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
t_obj				*sphere_malloc(t_vertex p, float rad, t_vector r, t_color c);
t_obj				*plane_malloc(t_vertex p, t_vector dir, t_vector normal, t_color c);
t_camera			*camera_malloc(t_vertex pos, t_vector orientation, float angle);
t_light				*light_malloc(t_vertex pos, t_color color);
/*
** Print functions
*/
void				print_matrix(t_matrix m);
int					print_objets(t_scene *scene);
int					print_camera(t_camera *cam);
int					print_vector(t_vector v);

/*
** Camera rotation and translation 
*/
int					rotation_type(t_vector a, t_vector b);
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
int					colorization(t_env *env, t_ray ray, double nearest, t_obj *sphere);
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
