/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 04:41:23 by toliver           #+#    #+#             */
/*   Updated: 2018/12/16 17:03:13 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_angles(void)
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

void			print_matrix(t_matrix m)
{
	printf("| %5f %5f %5f %5f |\n", m.matrix[0][0],m.matrix[0][1],m.matrix[0][2],m.matrix[0][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[1][0],m.matrix[1][1],m.matrix[1][2],m.matrix[1][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[2][0],m.matrix[2][1],m.matrix[2][2],m.matrix[2][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[3][0],m.matrix[3][1],m.matrix[3][2],m.matrix[3][3]);
	printf("\n");
}

void				print_vec(t_vec v)
{
	printf("[%f][%f][%f] [%f]\n", v.x, v.y, v.z, v.w);
}
