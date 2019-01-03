/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 22:39:18 by toliver          ###   ########.fr       */
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

# define OBJ_HIT_MODE 0
# define OBJ_HIT_LENGTH_MODE 1
# define RAY_COLOR_MODE 2
# define MODE_MAX 2

# include <stdio.h> // a suppr apres !

/*
 ** REORGANISATION DE .h
 */

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

t_args				*args_parsing(int ac, char **av);
t_args				*args_init(void);

void				verbose_args(t_args *args);
void				print_parse_mode(int mode);
void				print_renderer_mode(int mode);
void				print_print_mode(int mode);
void				print_verbose_mode(int mode);
void				print_debug_mode(int mode);
void				print_args_files(char **files);

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

t_scene				*json_parsing(char **files);
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
t_obj				*new_obj();
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
char				*string_to_lower(char *str);

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

t_ray				get_actual_ray(t_renderer *renderer, t_obj *cam, int x, int y);
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

void				malloc_raytracing(t_scene *scene, t_renderer *renderer, t_obj *camera);
void				stack_raytracing(t_scene *scene, t_renderer *renderer, t_obj *camera);
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
t_rgb				get_specular(t_ray *ray, t_ray to_light, t_obj *light, t_obj *cam);
t_rgb				get_diffuse(t_ray *ray, t_ray to_light, t_obj *light);
t_rgb				get_ambiant(t_ray *ray, t_scene *scene);
void				shoot_ray_lights(t_scene *scene, t_ray *ray, t_obj *cam);
void				shoot_ray(t_scene *scene, t_ray *ray);

/*
 ** END TO ORDER
 */


// to order but in structures malloc

t_matrix			world_to_obj_matrix(t_obj *obj);
t_matrix			obj_to_world_matrix(t_obj *obj);
t_obj				*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_rgb c);
t_obj				*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_rgb c);
void				obj_sphere_params(t_obj *obj, float radius);
void				obj_cylinder_params(t_obj *obj, float radius);
void				obj_cone_params(t_obj *obj, float angle);
void				obj_plane_params(t_obj *obj);
void				obj_camera_params(t_obj *obj, float fov);
void				obj_light_params(t_obj *obj, float intensity);

// end to order

void				running(t_args *args, t_scene *scenes);

void				verbose_running(t_args *args, t_scene *scenes);

/*
 ** PRINTING FUNCTIONS
 */

void				printing(t_args *args, t_scene *scenes, t_win *win, void *mlx);

void				verbose_printing(t_args *args, t_scene *scenes);

/*
 ** BASIC UTILS FUNCTIONS
 */

void				*ft_malloc(size_t size);
void				ft_error(char *str);

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
/*
 ** SINGLETON FUNCTIONS
 */

t_env				*env_get(void);
void				env_set(t_env *env);
t_args				*args_get(void);
void				args_set(t_args *arg);
int					step_get(void);
void				step_set(int value);


/*
 ** IN TESTING
 */

/*
   void				verbose();

   t_vec				get_updir(t_vec dir, t_vec right);
   t_vec				get_rightdir(t_vec dir);

   t_ray				ray_to_world(t_ray ray, t_obj *obj);
   t_ray				ray_to_obj(t_ray ray, t_obj *obj);
   t_ray				ray_init(t_vec pos, t_vec dir);
   t_ray				ray_init_lookat(t_vec pos, t_vec lookat);

   void				shoot_ray(t_ray *ray);
   float				sphere_radius(t_obj *sphere);
   int					is_equal_vector(t_vec a, t_vec b);
   int					is_opposite_vector(t_vec a, t_vec b);
   int					isequalfloat(float a, float b);

   void				tmp_parsing(void);
   void				json_parsing(void);
   */

/*
 ** STRUCTURES 
 */
/*
   t_obj				*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_rgb c);
   t_obj				*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_rgb c);
   void				obj_sphere_params(t_obj *obj, float radius);
   void				obj_cylinder_params(t_obj *obj, float radius);
   void				obj_cone_params(t_obj *obj, float angle);
   void				obj_plane_params(t_obj *obj);
   void				obj_camera_params(t_obj *obj, float fov);
   void				obj_light_params(t_obj *obj, float intensity);
   void				renderer_malloc(t_obj *camera);
   */

/*
 ** SINGLETON FUNCTIONS
 */
/*
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



   int					verbose_mode_get();
   int					print_mode_get();
   int					parse_mode_get();
   int					debug_mode_get();
   int					renderer_mode_get();
   char				**files_get();
   */


/*
 ** OBJET MALLOC
 */
/*
   t_obj				*obj_malloc_lookat(t_vec pos, t_vec lookat, t_vec up, t_rgb c);
   t_obj				*obj_malloc_dir(t_vec pos, t_vec dir, t_vec up, t_rgb c);
   void				obj_sphere_params(t_obj *obj, float radius);
   void				obj_cylinder_params(t_obj *obj, float radius);
   void				obj_cone_params(t_obj *obj, float angle);
   void				obj_plane_params(t_obj *obj);
   void				obj_camera_params(t_obj *obj, float fov);
   void				obj_light_params(t_obj *obj, float intensity);
   void				renderer_malloc(t_obj *camera);
   void				malloc_renderers(void);
   */
/*
 ** RAYTRACING FUNCTIONS
 */
/*
   t_vec				get_top_left_vec(t_obj *cam, t_vec *increment);
   t_vec				get_actual_dir(t_vec topleft, t_vec inc, int x, int y);
   t_ray				get_actual_ray(t_vec topleft, t_vec inc, int x, int y);

   void				raytracing_malloc(void);
   void				raytracing_stack(void);

   void				raytracing(void);
   void				raytracing_lights(void);
   void				shoot_ray(t_ray *ray);
   void				shoot_ray_lights(t_ray *ray);

   t_ray				reflect_ray(t_ray *ray);
   t_rgb				get_ambiant(t_ray *ray);
   t_rgb				get_specular(t_ray *ray, t_ray to_light, t_obj light);
   t_rgb				get_diffuse(t_ray *ray, t_ray to_light, t_obj light);
   */

/*
 ** INTERSECTION FUNCTIONS
 */
/*
   int					quadratic(float a, float b, float c, float l[2]);
   float				plane_intersection(t_ray ray, t_obj *plane);
   float				cone_intersection(t_ray ray, t_obj *cone);
   float				cylinder_intersection(t_ray ray, t_obj *cylinder);
   float				sphere_intersection(t_ray ray, t_obj *sphere);
   */
/*
 ** NORMAL FUNCTIONS
 */
/*
   void				get_normal(t_ray *ray);
   void				get_planenormal(t_ray *ray);
   void				get_cylindernormal(t_ray *ray);
   void				get_conenormal(t_ray *ray);
   void				get_spherenormal(t_ray *ray);
   void				get_normal(t_ray *ray);
   */
/*
 ** EVENT LISTENER
 */
/*
   void				events_listener(void);
   int					key_pressed(int key);
   int					mouse_move(int x, int y);
   */
/*
 ** MATRIX FUNCTIONS
 */
/*
   t_matrix			rotmatrix_axis_angle(t_vec v, float angle);
   t_matrix			world_to_obj_matrix(t_obj *obj);
   t_matrix			obj_to_world_matrix(t_obj *obj);
   */
/*
 ** MLX FUNCTIONS
 */
/*
   void				mlx_px_to_img(t_img *img, int x, int y, int color);
   */
/*
 ** PRINTING FUNCTIONS
 */
/*
   float				get_max_raylen(void);// kinda accessoire mais utile qu'ici.
   void				printing(void);
   void				print_cursor_over_image(void);
   void				print_final_ray_color_mode(void);
   void				print_obj_hit_color_length_mode(void);
   void				print_obj_hit_color_mode(void);
   */
/*
 ** COLOR HANDLING FUNCTIONS
 */
/*
   t_rgb				rgb_init(int value);
   t_rgb				rgb_add(t_rgb a, t_rgb b);
   t_rgb				rgb_mul(t_rgb a, float scalar);
   t_rgb				rgb_mul_rgb(t_rgb a, t_rgb b);
   void				rgb_updatevalue(t_rgb *rgb);
   */
/*
 ** TEMPORARY PARSING FUNCTIONS
 */
/*
   int					parse_2scene(void);
   void				camera_add(t_scene *scene, t_obj *camera);
   void				light_add(t_scene *scene, t_obj *light);
   void				obj_add(t_scene *scene, t_obj *obj);
   */
/* 
 ** DEBUG FUNCTIONS
 */
/*
   void				print_to_light_infos(t_ray *ray);
   void				print_obj_hit_infos(t_ray *ray);
   void				print_lightobj_hit_infos(t_ray *ray);
   void				display_cursor_infos(void);
   void				display_cursor_lightinfos(t_ray *ray);
   void				print_angles(void);
   void				print_matrix(t_matrix matrix);
   void				print_vec(t_vec v);
   void				print_objects(t_obj *obj, char *type);
   void				print_lights(t_scene *scene);
   void				print_cameras(t_scene *scene);
   void				print_scene(t_scene *scene);
   void				print_new_scene(t_scene *scene);
   void				print_renderer(t_ray *ray);
   void				print_ray(t_ray *ray);
   void				print_lightray(t_ray *ray);

   void				print_args(void);
   void				print_env(void);
   void				print_scenes(t_scene *scene);
   void				print_settings(void);
   void				print_running(void);
   */
#endif
