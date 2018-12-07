/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/07 16:14:39 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix			xrot_matrix(t_vec dir, t_vec right, t_vec up)
{
	t_vec			dir_nox;
	t_vec			up_nox;
	float			dirrot;
	float			dirrotangle;
	float			uprot;
	float			uprotangle;

	dir_nox = vec_init0(0, dir.y, dir.z);
	up_nox = vec_init0(0, up.y, up.z);
	if (vec_magnitude(dir_nox) == 0 || vec_magnitude(up_nox) == 0)
		return (identity_matrix_init());
	dir_nox = vec_norm(dir_nox);
	up_nox = vec_norm(up_nox);
	dirrot = clampf(vec_dotproduct(dir_nox, vec_z()), -1, 1);
	uprot = clampf(vec_dotproduct(up_nox, vec_y()), -1, 1);
//	printf("uprot : %.50f, dirrot : %.50f\n", uprot, dirrot);
	dirrotangle = acosf(dirrot);
	uprotangle = acosf(uprot);
//	printf("uprotangle : %f, dirrotangle : %f\n", radtodeg(uprotangle), radtodeg(dirrotangle));
	if (is_equal_float(dirrotangle, uprotangle))
	{
//		printf("same angle x\n");
		return (rotmatrix_axis_angle(vec_x(), -dirrotangle));
	}
	return (identity_matrix_init());
}

t_matrix			yrot_matrix(t_vec dir, t_vec right, t_vec up)
{
	t_vec			dir_noy;
	t_vec			right_noy;
	float			dirrot;
	float			dirrotangle;
	float			rightrot;
	float			rightrotangle;


	dir_noy = vec_init0(dir.x, 0, dir.z);
	right_noy = vec_init0(right.x, 0, right.z);
	if (vec_magnitude(right_noy) == 0 || vec_magnitude(dir_noy) == 0)
		return (identity_matrix_init());
	dir_noy = vec_norm(dir_noy);
	right_noy = vec_norm(right_noy);
	dirrot = clampf(vec_dotproduct(dir_noy, vec_z()), -1.0, 1.0);
	rightrot = clampf(vec_dotproduct(right_noy, vec_x()), -1.0, 1.0);
//	printf("dirrot : %.50f, rightrot : %.50f\n", dirrot, rightrot);
	dirrotangle = acosf(dirrot);
	rightrotangle = acosf(rightrot);
//	printf("dirrotangle : %f, rightrotangle : %f\n", radtodeg(dirrotangle), radtodeg(rightrotangle));
	if (is_equal_float(rightrotangle, dirrotangle))
	{
//		printf("same angle y\n");
		return(rotmatrix_axis_angle(vec_y(), -rightrotangle));
	}
	return (identity_matrix_init());
}

t_matrix			zrot_matrix(t_vec dir, t_vec right, t_vec up)
{
	t_vec			right_noz;
	t_vec			up_noz;
	float			rightrot;
	float			uprot;
	float			rightrotangle;
	float			uprotangle;

	right_noz = vec_init0(right.x, right.y, 0);
	up_noz = vec_init0(up.x, up.y, 0);

	if (vec_magnitude(right_noz) == 0 || vec_magnitude(up_noz) == 0)
		return (identity_matrix_init());
	right_noz = vec_norm(right_noz);
	up_noz = vec_norm(up_noz);
	rightrot = clampf(vec_dotproduct(right_noz, vec_x()), -1.0, 1.0);
	uprot = clampf(vec_dotproduct(up_noz, vec_y()), -1.0, 1.0);
//	printf("rightrot : %.50f, toprot : %.50f\n", rightrot, uprot);
	rightrotangle = acosf(rightrot);
	uprotangle = acosf(uprot);
//	printf("rightrotangle : %f, toprotangle : %f\n", radtodeg(rightrotangle), radtodeg(uprotangle));
	if (is_equal_float(rightrotangle, uprotangle))
	{
//		printf("same angle z\n");
		return(rotmatrix_axis_angle(vec_z(), rightrotangle));
	}
	return (identity_matrix_init());
}

int					main(int ac, char **av)
{
	t_env			*env;

//	test();
//	exit(1);
	env = env_init();
	env_set(env); // toujours init et set lenv avant tout;
	parse_scene(env); // puis parsing bidon
	scene_set(env->scene); // set la scene actuelle a la premiere
	camera_set(env->scene->cameras); // set la camera a la premiere;
	renderer_set(); // set le renderer a la camera actuelle;
	printf("settings done\n");
	raytracing();
	printf("raytracing first pass done\n");
	raytracing_lights();
	printf("raytracing lights pass done\n");
	printing();
	printf("printing done\n");
	events_listener(env);
	mlx_loop(mlx_get());
	(void)ac;
	(void)av;
	return (1);
}
