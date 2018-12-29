/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_this.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 04:27:28 by toliver           #+#    #+#             */
/*   Updated: 2018/12/29 10:10:02 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void					print_color(t_RGB color, char *name)
{
	ft_printf("%-10s : RGB[%f, %f, %f] HEX : #%X\n", name,
			color.r, color.g, color.b, color.value);
}

void			print_matrix(t_matrix m)
{
	ft_printf("| %5f %5f %5f %5f |\n", m.matrix[0][0], m.matrix[0][1],
			m.matrix[0][2], m.matrix[0][3]);
	ft_printf("| %5f %5f %5f %5f |\n", m.matrix[1][0], m.matrix[1][1],
			m.matrix[1][2], m.matrix[1][3]);
	ft_printf("| %5f %5f %5f %5f |\n", m.matrix[2][0], m.matrix[2][1],
			m.matrix[2][2], m.matrix[2][3]);
	ft_printf("| %5f %5f %5f %5f |\n", m.matrix[3][0], m.matrix[3][1],
			m.matrix[3][2], m.matrix[3][3]);
	ft_printf("\n");
}

void				print_vec(t_vec v)
{
	ft_printf("[%f][%f][%f] [%f]\n", v.x, v.y, v.z, v.w);
}

void	mlx_px_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x * 4 + y * img->width * 4] = (color & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 1] = ((color >> 8) & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 2] = ((color >> 16) & 0xff);
	img->img_str[x * 4 + y * img->width * 4 + 3] = 0;
}

