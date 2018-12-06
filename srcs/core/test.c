/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:43:22 by toliver           #+#    #+#             */
/*   Updated: 2018/12/06 22:24:45 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float				try_xangle(t_vec vec, float xangle, float oppxangle)
{
	t_vec			xrotvec;
	t_vec			oppxrotvec;
	t_matrix		xrotmatrix;
	t_matrix		oppxrotmatrix;

	xrotmatrix = rotmatrix_axis_angle(vec_x(), xangle);
	oppxrotmatrix = rotmatrix_axis_angle(vec_x(), oppxangle);
	xrotvec = vec_normalize(matrix_mult_vec(xrotmatrix, vec));
	oppxrotvec = vec_normalize(matrix_mult_vec(oppxrotmatrix, vec));
//	print_vec(xrotvec);
//	print_vec(oppxrotvec);
	if (is_equal_vec(xrotvec, vec_z()))
		return(xangle);
	if (is_equal_vec(oppxrotvec, vec_z()))
		return (oppxangle);
	if (is_equal_vec(xrotvec, vec_opposite(vec_z())))
		return (xangle);
	return (oppxangle);
}

float				try_yangle(t_vec dir_noy, float yangle, float oppyangle)
{
	t_vec			yrotvec;
	t_vec			oppyrotvec;
	t_matrix		yrotmatrix;
	t_matrix		oppyrotmatrix;

	yrotmatrix = rotmatrix_axis_angle(vec_y(), yangle);
	oppyrotmatrix = rotmatrix_axis_angle(vec_y(), oppyangle);
	yrotvec = vec_normalize(matrix_mult_vec(yrotmatrix, dir_noy));
	oppyrotvec = vec_normalize(matrix_mult_vec(oppyrotmatrix, dir_noy));
//	print_vec(xrotvec);
//	print_vec(oppxrotvec);
	if (is_equal_vec(yrotvec, vec_z()))
		return(yangle);
	return (oppyangle);

}

float				yangle_get(t_vec final_dir)
{
	t_vec			dir_noy;
	float			dotproduct_zpos;
	float			dotproduct_zneg;
	float			yangle;
	float			oppyangle;

	dir_noy = vec_init0(final_dir.x, 0, final_dir.z);
	if (vec_magnitude(dir_noy) == 0)
		return (0);
	dir_noy = vec_normalize(dir_noy);
	if (is_equal_vec(dir_noy, vec_z()))
		return (0);
	if (is_opposite_vec(dir_noy, vec_z()))
		return (degtorad(180));
	dotproduct_zpos = clampf(vec_dotproduct(dir_noy, vec_z()), -1, 1);
	dotproduct_zneg = clampf(vec_dotproduct(dir_noy, vec_opposite(vec_z())), -1, 1);
	if (dotproduct_zpos == 0)
	{
		yangle = degtorad(90);
		oppyangle = degtorad(-90);
	}
	else
	{
		yangle = acosf(dotproduct_zpos);
		oppyangle = -acosf(dotproduct_zneg);
	}
	printf("yangle %f, oppyangle %f\n", radtodeg(yangle), radtodeg(oppyangle));
	if (fabs(yangle) == fabs(oppyangle))
	{
		printf("tryyangle\n");
		return (try_yangle(dir_noy, yangle, oppyangle));
	}
	else if (fabs(yangle) < fabs(oppyangle))
	{
		printf(" < \n");
		return (try_yangle(dir_noy, yangle, -yangle));
	}
	printf("else\n");
	return (try_yangle(dir_noy, oppyangle, -oppyangle));
}

float				xangle_get(t_vec final_dir)
{
	t_vec			dir_nox;
	float			dotproduct_zpos;
	float			dotproduct_zneg;
	float			xangle;
	float			oppxangle;

	dir_nox = vec_init0(0, final_dir.y, final_dir.z);
	if (vec_magnitude(dir_nox) == 0)
		return (0);
	dir_nox = vec_norm(dir_nox);
	if (is_equal_vec(dir_nox, vec_z()) || is_opposite_vec(dir_nox, vec_z()))
		return (0);
//	print_vec(dir_nox);
//	print_vec(vec_z());
	dotproduct_zpos = clampf(vec_dotproduct(dir_nox, vec_z()), -1, 1);
	dotproduct_zneg = clampf(vec_dotproduct(dir_nox, vec_opposite(vec_z())), -1, 1);
//	printf("%f %f\n", dotproduct_zpos, dotproduct_zneg);
	if (dotproduct_zpos == 0)
	{
		printf("dotproduct = 0\n");
		xangle = degtorad(90);
		oppxangle = degtorad(-90);
	}
	else
	{
		xangle = acosf(dotproduct_zpos);
		oppxangle = -acosf(dotproduct_zneg);
	}
	printf("xangle %f, oppxangle %f\n", radtodeg(xangle), radtodeg(oppxangle));
	if (fabs(xangle) == fabs(oppxangle))
	{
		printf("tryxangle\n");
		return (try_xangle(dir_nox, xangle, oppxangle));
	}
	else if (fabs(xangle) < fabs(oppxangle))
	{
		printf("fabs xangle < fabs oppxangle\n");
		return (try_xangle(dir_nox, xangle, -xangle));
	}
	printf("else\n");
	return (try_xangle(dir_nox, oppxangle, -oppxangle));
	// appliquer la transformation a dir_nox et check s'il est aligne avec vec_z()
}

void				test_angles(t_vec final_dir)
{
	t_vec			dir;
	t_vec			up;
	t_vec			right;

	float			xangle;
	t_matrix		xrotmatrix;
	t_matrix		oppxrotmatrix;

	printf("given vector : ");
	print_vec(final_dir);
	dir = vec_z();
	up = vec_y();
	right = vec_x();
	final_dir = vec_norm(final_dir);
	xangle = xangle_get(final_dir);
	xrotmatrix = rotmatrix_axis_angle(vec_x(), xangle);
	oppxrotmatrix = rotmatrix_axis_angle(vec_x(), -xangle);
	
	t_vec			rotated_dir;
	t_vec			rotated_up;

	rotated_dir = vec_normalize(matrix_mult_vec(xrotmatrix, final_dir));
	printf("rotated vec ");
	print_vec(rotated_dir);
//	print_vec(rotated_dir);
	rotated_up = vec_normalize(matrix_mult_vec(oppxrotmatrix, up));
	printf("should have 0 as y\n");
/*
	printf("given dir: ");
	print_vec(final_dir);
	printf("rotated dir: ");
	print_vec(rotated_dir);
	printf("SHOULD BE dir: ");
	print_vec(vec_z());
*/
	float			yangle;
	t_matrix		yrotmatrix;
	t_matrix		oppyrotmatrix;

	yangle = yangle_get(rotated_dir);
	yrotmatrix = rotmatrix_axis_angle(vec_y(), yangle);
	oppyrotmatrix = rotmatrix_axis_angle(vec_y(), -yangle);

	rotated_dir = vec_normalize(matrix_mult_vec(yrotmatrix, rotated_dir));
	rotated_up = vec_normalize(matrix_mult_vec(oppyrotmatrix, rotated_up));

	printf("ce vecteur devrait etre : 0, 0, 1\n");
	print_vec(rotated_dir);
	//printf("dir should be :");
//	print_vec(vec_z());
//	printf("but is : ");
//	print_vec(rotated_dir);
	printf("up should should be : ");
	print_vec(rotated_up);
	printf("\n");
}

void				test(void)
{
	/*
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!!!!! MONO DIRECTION : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	test_angles(vec_init0(1, 0, 0));
	test_angles(vec_init0(-1, 0, 0));
	test_angles(vec_init0(0, 1, 0));
	test_angles(vec_init0(0, -1, 0));
	test_angles(vec_init0(0, 0, 1));
	test_angles(vec_init0(0, 0, -1));
	*/
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!!!!! TWO DIRECTION : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
//	test_angles(vec_init0(1, 1, 0));
//	test_angles(vec_init0(-1, 1, 0));
//	test_angles(vec_init0(1, -1, 0));
//	test_angles(vec_init0(-1, -1, 0));

//	test_angles(vec_init0(1, 0, 1));
//	test_angles(vec_init0(-1, 0, 1));
	test_angles(vec_init0(1, 0, -1));
	test_angles(vec_init0(-1, 0, -1));

//	test_angles(vec_init0(0, 1, 1));
//	test_angles(vec_init0(0, -1, 1));
	test_angles(vec_init0(0, 1, -1));
	test_angles(vec_init0(0, -1, -1));
	
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!! THREE DIRECTIONS : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

//	test_angles(vec_norm(vec_init0(1, 1, 1)));
	test_angles(vec_norm(vec_init0(1, 1, -1)));
//	test_angles(vec_norm(vec_init0(1, -1, 1)));
	test_angles(vec_norm(vec_init0(1, -1, -1)));

//	test_angles(vec_norm(vec_init0(-1, 1, 1)));
	test_angles(vec_norm(vec_init0(-1, 1, -1)));
//	test_angles(vec_norm(vec_init0(-1, -1, 1)));
	test_angles(vec_norm(vec_init0(-1, -1, -1)));
	exit(1);
}

