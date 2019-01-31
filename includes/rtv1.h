/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 21:52:51 by toliver           #+#    #+#             */
/*   Updated: 2019/01/31 22:12:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "libftg.h"
# include "libftprintf.h"
# include "json_parser.h"
# include "keys.h"
# include <limits.h>
# include "mlx_errors.h"
# include "rtv1_errors.h"
# include "rtv1_required_information.h"
# include "rtv1_struct.h"
# include "colors.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 768
# define TOLERANCE 0.01

/*
** BASIC VERBOSE
*/

void				print_angles(void);
void				print_matrix(t_matrix matrix);
void				print_vec(t_vec v);
void				print_color(t_rgb color, char *name);

/*
** ARGS PARSING
*/

t_args				*args_parsing(int ac, char**av);
t_args				*args_init(void);

void				verbose_args(t_args *args);
void				print_renderer_mode(int mode);
void				print_print_mode(int mode);
void				print_verbose_mode(int mode);
void				print_debug_mode(int mode);
void				print_args_files(char**files);

/*
** INIT FUNCTIONS
*/

t_env				*init(t_args *args);
t_env				*env_init(t_args *args);
t_win				*win_init(int width, int height, char *name, void *mlx);
t_img				*img_init(int width, int height, void *mlx);

void				verbose_env(t_env *env);
void				print_mlx(void *mlx);
void				print_mlximg(t_img *img);
void				print_window(t_win *win);

/*
** PARSING FUNCTIONS
*/

t_scene				*parsing(t_args *args);

void				verbose_parsing(t_scene *scene);
void				print_scene(t_scene *scene);
void				print_scenes(t_scene *scenes);
void				print_objects(t_obj *objs);
void				print_object(t_obj *obj);
void				print_object_common(t_obj *obj);
void				print_object_spec(t_obj *obj);
void				print_lights(t_obj *lights);
void				print_cameras(t_obj *cameras);

/*
** TMP PARSING FUNCTIONS
*/

t_scene				*tmp_parsing(void);

/*
** JSON PARSER PARSING
*/

t_scene				*rtv1_parsing(t_elem *elem);
t_scene				*parse_scene(t_elem *elem);
t_obj				*parse_objects(t_elem *elem);
t_obj				*parse_lights(t_elem *elem);
t_obj				*parse_cameras(t_elem *elem);
t_rgb				parse_color(t_elem *elem, int required);
void				parse_dir_lookat_pos(t_elem *elem, t_obj *obj);
void				parse_up_right_vec(t_elem *elem, t_obj *obj);
float				parse_float(t_elem *elem);
t_vec				parse_vector(t_elem *elem);
t_vec				parse_angle_vector(t_elem *elem);
t_obj				*parse_one_object(t_elem *elem,
		void (*parse_obj)(t_elem *elem, t_obj *obj));
t_obj				*new_obj(void);
float				parse_radius(float radius);
float				parse_degree_to_rad(float angle);
void				init_object(t_elem *elem, t_obj *obj);
void				init_cone(t_elem *elem, t_obj *obj);
void				init_plane(t_elem *elem, t_obj *obj);
void				init_cylinder(t_elem *elem, t_obj *obj);
void				init_sphere(t_elem *elem, t_obj *obj);
void				init_light(t_elem *elem, t_obj *obj);
void				init_camera(t_elem *elem, t_obj *obj);
float				required_float(float number, int required, char *error);
t_vec				required_vec(t_vec vec, int required, char *error);
float				default_float(float number, float def);
t_vec				default_vec(t_vec vec, t_vec def);
t_rgb				default_rgb(t_rgb rgb, t_rgb def);
t_elem				*find_elem_by_key(t_elem *elem, char *key);
int					check_type_of_key(char *key, t_json_data type);
int					check_float_keys(char *key);
int					check_int_keys(char *key);
int					hex_color_to_int(t_elem *elem);
t_rgb				parse_rgb(t_elem *elem, t_rgb color);
int					parse_hex(t_elem *elem);
t_rgb				parse_rgb_and_val(t_elem *child_elem);
t_vec				get_right_dir(t_vec dir);
t_vec				get_up_dir(t_vec dir, t_vec right);
t_vec				vec_rot_zaxis_angle(t_vec v, t_vec zaxis, float angle);

/*
** JSON PARSER ERRORS
*/

void				wrong_format(char *form, t_json_data type);
void				is_required(char *key, int one);

/*
** SETTINGS FUNCTIONS
*/

t_ray				ray_init_lookat(t_vec pos, t_vec lookat);
t_ray				ray_init(t_vec pos, t_vec dir);
t_ray				ray_to_obj(t_ray ray, t_obj *obj);
t_ray				ray_to_world(t_ray ray, t_obj *obj);

t_ray				get_actual_ray(t_renderer *renderer, t_obj *cam, int x,
						int y);
t_ray				*renderer_malloc(t_renderer *renderer, t_obj *cam);
t_renderer			*renderer_init(t_obj *cam, t_args *arg, t_env *env);
void				renderers_settings(t_args *args, t_env *env);
void				settings(t_args *args, t_env *env);

void				verbose_settings(t_args *args, t_env *env);
void				print_renderers(t_scene *scene);
void				print_renderer(t_renderer *renderer);

/*
** RUNNING FUNCTIONS
*/

t_ray				reflect_ray(t_ray *ray);
t_vec				reflect_vec(t_vec vec, t_vec axis);

/*
** PRIMITIVES FUNCTIONS
*/

void				get_conenormal(t_ray *ray);
void				get_cylindernormal(t_ray *ray);
void				get_planenormal(t_ray *ray);
void				get_spherenormal(t_ray *ray);

float				sphere_radius(t_obj *sphere);
void				sphere_intersection(t_ray *ray, t_obj *sphere);
void				plane_intersection(t_ray *ray, t_obj *plane);
void				cylinder_intersection(t_ray *ray, t_obj *plane);
void				cone_intersection(t_ray *ray, t_obj *cone);

int					quadratic(float a, float b, float c, float l[2]);
void				check_for_closest(float length, t_ray *ray, t_obj *obj);
void				get_normal(t_ray *ray);

/*
**	RAYTRACING FUNCTIONS
*/

void				malloc_raytracing(t_scene *scene, t_renderer *renderer,
						t_obj *camera);
void				stack_raytracing(t_scene *scene, t_renderer *renderer,
						t_obj *camera);
void				raytracing(t_scene *scene, t_obj *camera);

/*
** TO ORDER INSIDE RUNNING
*/

void				print_color(t_rgb color, char *name);
void				print_matrix(t_matrix m);
void				print_vec(t_vec v);
void				mlx_px_to_img(t_img *img, int x, int y, int color);
t_ray				reflect_ray(t_ray *ray);
t_vec				reflect_vector(t_vec vec, t_vec axis);
t_rgb				get_specular(t_ray *ray, t_ray to_light, t_obj *light,
						t_obj *cam);
t_rgb				get_diffuse(t_ray *ray, t_ray to_light, t_obj *light);
t_rgb				get_ambiant(t_ray *ray, t_scene *scene);
void				shoot_ray_lights(t_scene *scene, t_ray *ray, t_obj *cam);
void				shoot_ray(t_scene *scene, t_ray *ray);

t_matrix			world_to_obj_matrix(t_obj *obj);
t_matrix			obj_to_world_matrix(t_obj *obj);

/*
** END TO ORDER
*/

void				running(t_args *args, t_scene *scenes);

void				verbose_running(t_args *args, t_scene *scenes);

/*
** PRINTING FUNCTIONS
*/

void				printing(t_args *args, t_scene *scenes, t_win *win,
						void *mlx);

void				verbose_printing(t_args *args, t_scene *scenes);

/*
** LOOP FUNCTIONS
*/

int					key_pressed(int key, t_env *env);
void				loop(t_args *args, t_env *env);
void				free_env(t_env *env);

void				verbose_loop(t_args *args, t_env *env);

/*
** BASIC UTILS FUNCTIONS
*/

void				*ft_malloc(size_t size);
void				ft_error(char *str);
char				*string_to_lower(char *str);

/*
** BASIC MATH UTILS FUNCTIONS
*/

float				maxf(float a, float b);
float				minf(float a, float b);
int					clampi(int a, int inf_limit, int sup_limit);
float				clampf(float a, float inf_limit, float sup_limit);
int					is_equal_float(float a, float b);
int					is_equal_vec(t_vec a, t_vec b);
int					is_opposite_vec(t_vec a, t_vec b);
#endif
