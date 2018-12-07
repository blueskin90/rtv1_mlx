/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:43:22 by toliver           #+#    #+#             */
/*   Updated: 2018/12/07 16:16:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				test_angles(t_vec not_norm_dir)
{
	t_vec			dir;
	t_vec			up;
	t_vec			right;

	dir = vec_normalize(not_norm_dir);
	right = get_rightdir(dir);
	up = get_updir(dir, right);
	printf("new_obj :\n");
	printf("not normalized dir : ");
	print_vec(not_norm_dir);
	printf("dir :");
	print_vec(dir);
	printf("right :");
	print_vec(right);
	printf("up :");
	print_vec(up);	
}

void				test(void)
{
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!!!!! MONO DIRECTION : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	test_angles(vec_init0(1, 0, 0));
	test_angles(vec_init0(-1, 0, 0));
	test_angles(vec_init0(0, 1, 0));
	test_angles(vec_init0(0, -1, 0));
	test_angles(vec_init0(0, 0, 1));
	test_angles(vec_init0(0, 0, -1));
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!!!!! TWO DIRECTION : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	test_angles(vec_init0(1, 1, 0));
	test_angles(vec_init0(-1, 1, 0));
	test_angles(vec_init0(1, -1, 0));
	test_angles(vec_init0(-1, -1, 0));

	test_angles(vec_init0(1, 0, 1));
	test_angles(vec_init0(-1, 0, 1));
	test_angles(vec_init0(1, 0, -1));
	test_angles(vec_init0(-1, 0, -1));

	test_angles(vec_init0(0, 1, 1));
	test_angles(vec_init0(0, -1, 1));
	test_angles(vec_init0(0, 1, -1));
	test_angles(vec_init0(0, -1, -1));
	
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	printf("!!!!!!!!!!!!!!!!!! THREE DIRECTIONS : \n");
	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

	test_angles(vec_init0(1, 1, 1));
	test_angles(vec_init0(1, 1, -1));
	test_angles(vec_init0(1, -1, 1));
	test_angles(vec_init0(1, -1, -1));

	test_angles(vec_init0(-1, 1, 1));
	test_angles(vec_init0(-1, 1, -1));
	test_angles(vec_init0(-1, -1, 1));
	test_angles(vec_init0(-1, -1, -1));
	exit(1);
}

