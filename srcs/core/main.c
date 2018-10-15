/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2018/10/15 06:10:32 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					main(void)
{
	t_vertex vtx0 = vertex_init(0, 0, 0);
	t_vertex vtxX = vertex_init(1, 0, 0);
	t_vertex vtxY = vertex_init(0, 1, 0);
	t_vertex vtxZ = vertex_init(0, 0, 1);

	t_vector vtcXunit = vector_init(vtx0, vtxX);
	t_vector vtcYunit = vector_init(vtx0, vtxY);
	t_vector vtcZunit = vector_init(vtx0, vtxZ);
	t_vector vtc0unit = vector_init(vtx0, vtx0);

	printf("x = %f, y = %f, z = %f\n", vtcXunit.x, vtcXunit.y, vtcXunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcYunit.x, vtcYunit.y, vtcYunit.z);
	printf("x = %f, y = %f, z = %f\n", vtcZunit.x, vtcZunit.y, vtcZunit.z);

	t_vertex dest1 = vertex_init(-12.34, 23.45, -34.56);
	t_vector vtc1 = vector_init(vtx0, dest1);
	printf("x = %f, y = %f, z = %f\n", vtc1.x, vtc1.y, vtc1.z);
	t_vertex orig2 = vertex_init(23.87, -37.95, 78.34);
	t_vertex dest2 = vertex_init(-12.34, 23.45, -34.56);
	t_vector vtc2 = vector_init(orig2, dest2);
	printf("x = %f, y = %f, z = %f\n", vtc2.x, vtc2.y, vtc2.z);
	printf("Magnitude is %f\n", vector_magnitude(vtc2));

	t_vector nVtc2 = vector_normalize(vtc2);
	printf("nvtc2 = x = %f, y = %f, z = %f\n", nVtc2.x, nVtc2.y, nVtc2.z);
	printf("Magnitude is %f\n", vector_magnitude(nVtc2));
	t_vector vtcadd = vector_add(vtc1, vtc2);
	printf("addition = x = %f, y = %f, z = %f\n", vtcadd.x, vtcadd.y, vtcadd.z);
	t_vector vtcsub = vector_sub(vtc1, vtc2);
	printf("soustraction = x = %f, y = %f, z = %f\n", vtcsub.x, vtcsub.y, vtcsub.z);
	t_vector vtcopp = vector_opposite(vtc1);
	printf("oppose = x = %f, y = %f, z = %f\n", vtcopp.x, vtcopp.y, vtcopp.z);
	t_vector vtcmul = vector_mul(vtc1, 42);
	printf("mul = x = %f, y = %f, z = %f\n", vtcmul.x, vtcmul.y, vtcmul.z);
	t_vector vtcdiv = vector_div(vtc1, 42);
	printf("div = x = %f, y = %f, z = %f\n", vtcdiv.x, vtcdiv.y, vtcdiv.z);
	printf("dot product vtc1 et vtc2 = %f\n", vector_dotproduct(vtc1, vtc2));
	printf("cos de vtc1 et 2 = %f\n", vector_cos(vtc1, vtc2));
	printf("cos de vtcxunit et vtcyunit = %f\n", vector_cos(vtcXunit, vtcYunit));
	t_vector vtccross = vector_crossproduct(vtc1, vtc2);
	t_vector vtccross2 = vector_crossproduct(vtcXunit, vtcYunit);
	printf("x = %f, y = %f, z = %f\n", vtccross.x, vtccross.y, vtccross.z);
	printf("x = %f, y = %f, z = %f\n", vtccross2.x, vtccross2.y, vtccross2.z);
	return (0);
}
