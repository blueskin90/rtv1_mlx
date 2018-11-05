/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 18:23:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "mlx.h"
# include "libft.h"
# include "libftg.h"

# define MALLOC_FAIL "Malloc failed\n"
# define MLX_FAIL "Couldn't start MLX\n"
# define WINDOW_FAIL "Couldn't open a new window\n"
# define MLX_IMG_FAIL "MLX couldn't get a new image\n"

/*
** struct of objects
*/


typedef struct		s_camera
{
	t_vertex		pos;
	t_vector		orientation;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_viewplane
{
	float			width;
	float			height;
}					t_viewplane;

typedef struct		s_sphere
{
	float			radius;
	t_vertex		center;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct		s_light
{
	t_vertex		pos;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_scene
{
	t_sphere		*sphere;
	t_light			*light;
}					t_scene;

/*
** End of struct object
*/




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

#endif
