/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 19:03:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/18 17:46:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

int					test(void)
{
	t_vec vtx0 = vec_init0(0, 0, 0);
	t_vec vtxX = vec_init0(1, 0, 0);
	t_vec vtxY = vec_init0(0, 1, 0);
	t_vec vtxZ = vec_init0(0, 0, 1);

	t_vec vtcXunit = vec_init(vtx0, vtxX);
	t_vec vtcYunit = vec_init(vtx0, vtxY);
	t_vec vtcZunit = vec_init(vtx0, vtxZ);
	t_vec vtc0unit = vec_init(vtx0, vtx0);

	printf("x = %f, y = %f, z = %f\n", vtcXunit.x, vtcXunit.y, vtcXunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcYunit.x, vtcYunit.y, vtcYunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcZunit.x, vtcZunit.y, vtcZunit.z);

	t_vec dest1 = vec_init0(-12.34, 23.45, -34.56);
	t_vec vtc1 = vec_init(vtx0, dest1);
	printf("x = %f, y = %f, z = %f\n", vtc1.x, vtc1.y, vtc1.z);
	t_vec orig2 = vec_init0(23.87, -37.95, 78.34);
	t_vec dest2 = vec_init0(-12.34, 23.45, -34.56);
	t_vec vtc2 = vec_init(orig2, dest2);
	printf("x = %f, y = %f, z = %f\n", vtc2.x, vtc2.y, vtc2.z);
	printf("Magnitude is %f\n", vec_magnitude(vtc2));

	t_vec nVtc2 = vec_normalize(vtc2);
	printf("nvtc2 = x = %f, y = %f, z = %f\n", nVtc2.x, nVtc2.y, nVtc2.z);
	printf("Magnitude is %f\n", vec_magnitude(nVtc2));
	t_vec vtcadd = vec_add(vtc1, vtc2);
	printf("addition = x = %f, y = %f, z = %f\n", vtcadd.x, vtcadd.y, vtcadd.z);
	t_vec vtcsub = vec_sub(vtc1, vtc2);
	printf("soustraction = x = %f, y = %f, z = %f\n", vtcsub.x, vtcsub.y, vtcsub.z);
	t_vec vtcopp = vec_opposite(vtc1);
	printf("oppose = x = %f, y = %f, z = %f\n", vtcopp.x, vtcopp.y, vtcopp.z);
	t_vec vtcmul = vec_mul(vtc1, 42);
	printf("mul = x = %f, y = %f, z = %f\n", vtcmul.x, vtcmul.y, vtcmul.z);
	t_vec vtcdiv = vec_div(vtc1, 42);
	printf("div = x = %f, y = %f, z = %f\n", vtcdiv.x, vtcdiv.y, vtcdiv.z);
	printf("dot product vtc1 et vtc2 = %f\n", vec_dotproduct(vtc1, vtc2));
	printf("cos de vtc1 et 2 = %f\n", vec_cos(vtc1, vtc2));
	printf("cos de vtcxunit et vtcyunit = %f\n", vec_cos(vtcXunit, vtcYunit));
	t_vec vtccross = vec_crossproduct(vtc1, vtc2);
	t_vec vtccross2 = vec_crossproduct(vtcXunit, vtcYunit);
	printf("x = %f, y = %f, z = %f\n", vtccross.x, vtccross.y, vtccross.z);
	printf("x = %f, y = %f, z = %f\n", vtccross2.x, vtccross2.y, vtccross2.z);

	printf("identity\n");
	t_matrix identity = identity_matrix_init();
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", identity.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("translation\n");
	t_matrix translation = translation_matrix_init(vec_init(vec_init0(0,0,0), vec_init0(20, 20, 0)));
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", translation.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("scale\n");
	t_matrix scale = scale_matrix_init(10);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", scale.matrix[y][x]);
		printf("\n");
	}
	printf("\n");


	printf("ROTX\n");
	t_matrix rotx = rotx_matrix_init(45);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", rotx.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("ROTY\n");
	t_matrix roty = roty_matrix_init(90);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", roty.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	printf("ROTZ\n");
	t_matrix rotz = rotz_matrix_init(360);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", rotz.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	t_matrix multiplied = translation;

	printf("mult\n");
	multiplied = matrix_mult(matrix_mult(matrix_mult(matrix_mult(translation, rotx), roty), rotz), scale);
	for (int y = 0; y < 4; y++)
	{
		for(int x = 0; x < 4; x++)
			printf("[%f]", multiplied.matrix[y][x]);
		printf("\n");
	}
	printf("\n");

	t_vec vtxA = vec_init0(1, 1, 0);
	t_vec vtcmat = matrix_mult_vec(multiplied, vtxA);
	printf("soustraction = x = %f, y = %f, z = %f w = %f\n", vtcmat.x, vtcmat.y, vtcmat.z, vtcmat.w);
	return (0);
}

