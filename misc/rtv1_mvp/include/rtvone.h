/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtvone.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 17:43:01 by nfinkel           #+#    #+#             */
/*   Updated: 2018/11/03 18:19:52 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTVONE_H
# define RTVONE_H

# include <libft.h>
# include <mlx.h>
# include "utils.h"
# define WIN_X 640
# define WIN_Y 480

typedef enum	e_type
{
	E_SPHERE = 0,
}				t_type;

typedef struct	s_cam
{
	double		fov;
	double		angle;
	double		ratio_x;
	double		ratio_y;
	t_v3		pt;
}				t_cam;

typedef struct	s_obj
{
	double		scale;
	t_type		type;
	t_v3		pt;
	size_t		color;
}				t_obj;

typedef struct	s_env
{
	t_mlx		*mlx;
	t_cam		*cam;
	t_obj		**objs;
	uint16_t	height;
	double		invHeight;
	uint16_t	hx;
	uint16_t	width;
	double		invWidth;
	uint16_t	hy;
	t_v3		light;
	double		low_light;
	double		high_light;
	double		nbr_light;
	double		total_light;
}				t_env;

typedef int		(*t_f)(t_v3 *, const t_v3 *, t_obj *);

t_obj			**add_objs(void);
void			terminate(t_env *env);

/*
** HOOKS
*/
void			events_listener(t_env env);
void			key(int key, t_env *env);
void			pos_notify(int x, int y, t_env *env);// A SUPPRIMER

/*
** INTERSECTION WITH FORMS
*/
int				in_sphere(t_v3 *vec_r, const t_v3 *vec_o, t_obj *circle);
/*
** RENDER & TRACE
*/
void			render(t_env env);
void			trace(t_env env, t_v3 *ray, int x, int y);
double			intersection_distance(t_env env, t_v3 *raydir,
				t_v3 *rayorig, int *obj_index);
unsigned int	colorization(t_env env, t_v3 *ray, double near, int obj_index);
double			cam_to_world_x(double x, t_env *env);
double			cam_to_world_y(double y, t_env *env);
double			world_to_cam_x(double xx, t_env *env);
double			world_to_cam_y(double yy, t_env *env);
/*
** VECTORS
*/
t_v3	ft_v3_sustract(const t_v3 *a, const t_v3 *b);
t_v3	ft_v3_add(const t_v3 *a, const t_v3 *b);
t_v3	ft_v3_div(const t_v3 *a, const t_v3 *b);
t_v3	ft_v3_multi(const t_v3 *a, const t_v3 *b);
t_v3	ft_v3_scalar(const t_v3 *a, double s);
double	ft_v3_dot(const t_v3 *a, const t_v3 *b);
#endif
