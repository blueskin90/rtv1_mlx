/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 01:55:56 by toliver           #+#    #+#             */
/*   Updated: 2018/12/01 04:37:57 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				angles_print(void)
{
	int				angle;

	angle = -360;
	while (angle <= 360)
	{
		printf("cos : %d degree = %f rad = %f\n", angle, cosf(degtorad(angle)), degtorad(angle));
		angle +=45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("sin : %d degree = %f rad = %f\n", angle, sinf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
	angle = -360;
	while (angle <= 360)
	{
		printf("tan : %d degree = %f rad = %f\n", angle, tanf(degtorad(angle)), degtorad(angle));
		angle += 45;
	}
	printf("\n");
}

t_camera			**camera_getptr()
{
	static t_camera	*ptr = NULL;
	return (&ptr);
}

t_camera			*camera_get()
{
	return (*(camera_getptr()));
}

int					camera_set(t_camera *camera)
{
	t_camera		**ptr;

	ptr = camera_getptr();
	*ptr = camera;
	return (1);
}


t_scene				**scene_getptr()
{
	static t_scene	*ptr = NULL;
	return (&ptr);
}

t_scene				*scene_get()
{
	return (*(scene_getptr()));
}

int					scene_set(t_scene *scene)
{
	t_scene			**ptr;

	ptr = scene_getptr();
	*ptr = scene;
	return (1);
}

t_env				**env_getptr()
{
	static t_env	*ptr = NULL;
	return (&ptr);
}

t_env				*env_get()
{
	return (*(env_getptr()));
}

int					env_set(t_env *env)
{
	t_env			**ptr;

	ptr = env_getptr();
	*ptr = env;
	return (1);
}

int					win_get()
{
	return(env_get()->win);
}

int					win_getx()
{
	return(env_get()->win->winx);
}

int					win_gety()
{
	return(env_get()->win->winy);
}
int					rayinitialize(t_ray *ray, t_vec dir, t_matrix matrix)
{
	t_vec			finalpos;
	t_vec			finalrot;

	ft_bzero(ray, sizeof(t_ray));
	ray->origin = vec_opposite(camera_get()->pos);
	finalrot = vec_add(dir, camera_get()->pos);
	ray->direction = matrix_mult_vec(matrix, vec_sub(dir, ray->origin));
	return (1);
}

t_ray				**ray_getptr()
{
	static t_ray	*ptr = NULL;
	return (&ptr);
}

t_ray				*ray_get(int x, int y)
{
	return (*(ray_getptr() + (x * y)));
}

int					ray_set(t_ray *ray)
{
	t_ray			**ptr;

	ptr = ray_getptr();
	*ptr = ray;
	return (1);
}

t_matrix			cam_to_world_matrix()
{
	float			angle;
	t_vec			axis;
	t_matrix		matrix;

	angle = acos(vec_dotproduct(camera_get()->orientation, vec_init0(0,0,1)));
	axis = vec_normalize(vec_opposite(vec_crossproduct(camera_get()->orientation, vec_init0(0,0,1))));
	if (vec_magnitude(axis) == 0)
		matrix = identity_matrix_init();
	else
		matrix = rotmatrix_axis_angle(axis, angle);
	matrix.matrix[0][3] = -camera_get()->pos.x;
	matrix.matrix[1][3] = -camera_get()->pos.y;
	matrix.matrix[2][3] = -camera_get()->pos.z;
	return (matrix);
}

int					rays_free()
{
	free(*ray_getptr());
	return (1);
}


/*
int					rays_init(int x, int y)
{
	t_matrix		matrix;
	t_vec			increment;
	t_vec			topleft;
	int				xi;
	int				yi;

	increment = vec_init0(0, 0, 0);
	topleft = get_top_left_vec(camera_get(), env_get()->win, &increment.x, &increment.y);
	if (ray_getptr() != NULL && *ray_getptr() != NULL)
		free((*ray_getptr()));
	if (!(*(ray_getptr()) = (t_ray*)malloc(sizeof(t_ray) * x * y)))
		return (0);
	matrix = cam_to_world_matrix();
	yi = 0;
	while (yi < WIN_HEIGHT)
	{
		xi = 0;
		while (xi < WIN_WIDTH)
		{
			ray_initialize(*(ray_getptr() + xi * yi), vec_init(topleft.x + increment.x * x, topleft.y + increment.y * y, topleft.z), matrix); 
			xi++;
		}
		yi++;
	}
	return (1);
}
 // penser a scene free et cam free;
*/

int				rays_init()
{
	scene_set(env_get()->scene);
	camera_set(env_get()->camera);
	return (1);
}

int				debug_mode(char **av)
{
	t_env		*env;

	(void)av;
//	angles_print();
 // init
	env = env_init();
	parse_scene(env);
	env_set(env);
	rays_init();
// fin de l'init
	camera_set(env->camera); // setter and getter of current scene / camera
	scene_set(env->scene);
	return (1);
}
