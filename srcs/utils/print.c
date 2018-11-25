
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:38:54 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/09 18:47:58 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// ATTENTIOB VRAI PRINTF
void			print_matrix(t_matrix m)
{
	printf("| %5f %5f %5f %5f |\n", m.matrix[0][0],m.matrix[0][1],m.matrix[0][2],m.matrix[0][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[1][0],m.matrix[1][1],m.matrix[1][2],m.matrix[1][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[2][0],m.matrix[2][1],m.matrix[2][2],m.matrix[2][3]);
	printf("| %5f %5f %5f %5f |\n", m.matrix[3][0],m.matrix[3][1],m.matrix[3][2],m.matrix[3][3]);
	printf("\n");
}

int					print_objets(t_scene *scene)
{
	t_obj			*ptr;
	t_light			*ptr2;
	int				i;

	ptr = scene->objs;
	i = 1;
	while (ptr)
	{
		if (ptr->type == SPHERE)
		{
			printf("SPHERE NUMBER %d\ncenter = [%.2f][%.2f][%.2f]\nRadius = %f\norientation = [%.2f][%.2f][%.2f]\ncolor = [%d][%d][%d]\n\n", i, ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->params.sphere.radius, ptr->rotx, ptr->roty, ptr->rotz, ptr->color.rgb.r, ptr->color.rgb.g, ptr->color.rgb.b);
		}
		i++;
		ptr = ptr->next;
	}
	ptr2 = scene->light;
	i = 1;
	while (ptr2)
	{
		printf("LIGHT NUMBER %d\npos = [%.2f][%.2f][%.2f]\ncolor = [%d][%d][%d]\n\n", i, ptr2->pos.x, ptr2->pos.y, ptr2->pos.z, ptr2->color.rgb.r, ptr2->color.rgb.g, ptr2->color.rgb.b);
		i++;
		ptr2 = ptr2->next;
	}
	printf("\n");
	return (1);
}
int					print_camera(t_camera *cam)
{
	t_camera		*ptr;

	ptr = cam;
	while (ptr)
	{
		printf("CAMERA (actually only one)\npos = [%.2f][%.2f][%.2f]\norientation = [%.2f][%.2f][%.2f]\n\n", ptr->pos.x, ptr->pos.y, ptr->pos.z, ptr->orientation.x, ptr->orientation.y, ptr->orientation.z);
		ptr = ptr->next;
	}
	printf("\n");
	return (1);
}

int					print_vec(t_vec v)
{
	printf("[%f][%f][%f] [%f]\n", v.x, v.y, v.z, v.w);
	return (1);
}
