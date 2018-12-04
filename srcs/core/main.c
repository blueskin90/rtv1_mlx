/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/04 19:15:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_matrix			world_to_obj(t_vec dir, t_vec right, t_vec up, t_vec pos)
{
	t_matrix		matrix;

	matrix = translation_matrix_init(vec_opposite(pos));
	return (matrix);
}

/*
float				get_xangle(t_vec dir, t_vec up)
{
	t_vec			dir_nox;
	t_vec			up_nox;
	float			angle;
	float			dotproductdir;
	float			dotproductup;

	dir_nox = vec_init0(0, dir.y, dir.z);
	up_nox = vec_init0(0, up.y, up.z);
	dotproduct = 0;
	if (vec_magnitude(dir_nox) == 0 || vec_magnitude(up_nox) == 0)
		angle = 0;
	else
	{
		dir_nox = vec_normalize(dir_nox);
		up_nox = vec_normalize(up_nox);
		dotproductdir = vec_dotproduct(dir_nox, vec_z());
		dotproductup = vec_dotproduct(up_nox, vec_y());
		if (dotproductdir > 1)
			dotproductdir = 1;
		if (dotproductdir < -1)
			dotproductdir = -1;
		angle = -acosf(dotproduct);
	}
//	printf("x angle = %f rad\n", xangle);
	printf("x angle = %f deg\n", radtodeg(angle));
	return (angle);
}

void				test_rotangles(t_vec dir, t_vec right, t_vec up)
{
	float			xangle;
	float			yangle;
	float			zangle;
	float			dotproduct;
	
	t_vec			right_noy;
	t_vec			up_noz;

	printf("	====== TEST_ROTANGLES =======\n");
	xangle = get_xangle(dir, up);
	right_noy = vec_init0(right.x, 0, right.z);
	dotproduct = 0;
	if (vec_magnitude(right_noy) == 0)
		yangle = 0;
	else
	{
		right_noy = vec_normalize(right_noy);
		dotproduct = vec_dotproduct(right_noy, vec_x());
		if (dotproduct > 1)
			dotproduct = 1;
		if (dotproduct < -1)
			dotproduct = -1;
		yangle = -acosf(dotproduct);
	}
//	printf("y angle = %f rad\n", yangle);
	printf("y angle = %f deg\n", radtodeg(yangle));

	up_noz = vec_init0(up.x, up.y, 0);
	dotproduct = 0;
	if (vec_magnitude(up_noz) == 0)
		zangle = 0;
	else
	{
		up_noz = vec_normalize(up_noz);
		dotproduct = vec_dotproduct(up_noz, vec_y());
		if (dotproduct > 1)
			dotproduct = 1;
		if (dotproduct < -1)
			dotproduct = -1;
		zangle = -acosf(dotproduct);
	}
//	printf("z angle = %f rad\n", zangle);
	printf("z angle = %f deg\n", radtodeg(zangle));

	printf("	////// TEST_ROTANGLES \\\\\\\\\\\\\n");
}
*/

 // SI ANGLE POUR ALIGNER les 2 vecteurs concernes par la rotation dudit axe pas pareil -> on aligne pas, sinon -> go aligner;

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
	printf("uprot : %.50f, dirrot : %.50f\n", uprot, dirrot);
	dirrotangle = acosf(dirrot);
	uprotangle = acosf(uprot);
	printf("uprotangle : %f, dirrotangle : %f\n", radtodeg(uprotangle), radtodeg(dirrotangle));
	if (is_equal_float(dirrotangle, uprotangle))
	{
		printf("same angle x\n");
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
	printf("dirrot : %.50f, rightrot : %.50f\n", dirrot, rightrot);
	dirrotangle = acosf(dirrot);
	rightrotangle = acosf(rightrot);
	printf("dirrotangle : %f, rightrotangle : %f\n", radtodeg(dirrotangle), radtodeg(rightrotangle));
	if (is_equal_float(rightrotangle, dirrotangle))
	{
		printf("same angle y\n");
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
	printf("rightrot : %.50f, toprot : %.50f\n", rightrot, uprot);
	rightrotangle = acosf(rightrot);
	uprotangle = acosf(uprot);
	printf("rightrotangle : %f, toprotangle : %f\n", radtodeg(rightrotangle), radtodeg(uprotangle));
	if (is_equal_float(rightrotangle, uprotangle))
	{
		printf("same angle z\n");
		return(rotmatrix_axis_angle(vec_z(), rightrotangle));
	}
	return (identity_matrix_init());
}

void				apply_matrix(t_matrix matrix, t_vec *dir, t_vec *right, t_vec *up)
{
	*dir = vec_norm(matrix_mult_vec(matrix, *dir));
	*right = vec_norm(matrix_mult_vec(matrix, *right));
	*up = vec_norm(matrix_mult_vec(matrix, *up));
}

void				test_angles(t_vec orig_dir)
{
	t_vec			dir;
	t_vec			right;
	t_vec			up;

	t_matrix		zrotmatrix;
	t_matrix		yrotmatrix;
	t_matrix		xrotmatrix;
	t_matrix		finalmatrix;
	dir = vec_normalize(orig_dir);
	right = get_rightdir(dir);
	up = get_updir(dir, right);
	printf("========== TEST_ANGLES ==========\n");
	printf("basic values : \n");
	printf("dir : ");
	print_vec(dir);
	printf("up : ");
	print_vec(up);
	printf("right : ");
	print_vec(right);
	printf("\nzrot values : \n");
	zrotmatrix = zrot_matrix(dir, right, up);
	apply_matrix(zrotmatrix, &dir, &right, &up);
	printf("dir : ");
	print_vec(dir);
	printf("up : ");
	print_vec(up);
	printf("right : ");
	print_vec(right);
	printf("\nyrot values : \n");
	yrotmatrix = yrot_matrix(dir, right, up);
	apply_matrix(yrotmatrix, &dir, &right, &up);
	printf("dir : ");
	print_vec(dir);
	printf("up : ");
	print_vec(up);
	printf("right : ");
	print_vec(right);
	printf("\nxrot values : \n");
	xrotmatrix = xrot_matrix(dir, right, up);
	apply_matrix(xrotmatrix, &dir, &right, &up);
	printf("dir : ");
	print_vec(dir);
	printf("up : ");
	print_vec(up);
	printf("right : ");
	print_vec(right);
	printf("\n FINAL VALUES \n");
	finalmatrix = matrix_mult(matrix_mult(zrotmatrix, yrotmatrix), xrotmatrix);
	printf("dir : ");
	print_vec(dir);
//	print_vec(vec_normalize(matrix_mult_vec(finalmatrix, dir)));
	printf("up : ");
	print_vec(up);
//	print_vec(vec_normalize(matrix_mult_vec(finalmatrix, up)));
	printf("right : ");
	print_vec(right);
//	print_vec(vec_normalize(matrix_mult_vec(finalmatrix, right)));
	printf("/========\\ TEST_ANGLES /=========\\\n\n\n");
}

void				test(void)
{
	test_angles(vec_init0(0, 1, 1));
	test_angles(vec_init0(1, 1, 0));
	test_angles(vec_init0(1, 0, 1));
	test_angles(vec_init0(1, 0, -1));
	test_angles(vec_init0(0, -1, 1));
	test_angles(vec_init0(-1, 1, 0));
	exit(1);
}
// penser si l'axe est pile a l'oppose
int					main(int ac, char **av)
{
	t_env			*env;

	test();
	exit(1);
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
