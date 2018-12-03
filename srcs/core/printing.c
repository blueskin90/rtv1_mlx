/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 06:47:57 by toliver           #+#    #+#             */
/*   Updated: 2018/12/03 07:11:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_obj_hit_color_mode(void)
{
	int				x;
	int				y;
	t_ray			*ray;

	y = 0;
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			ray = renderer_getray(x + y * win_getx());
			if (ray->length != INFINITY)
				mlx_px_to_img(env_get()->win->img, x, y, ray->obj_hit->color.rgb.value);
			else
				mlx_px_to_img(env_get()->win->img, x, y, 0);
			x++;
		}
		y++;
	}
}

float				get_max_raylen(void)
{
	int				i;
	float			lenmax;
	t_ray			*ray;

	i = 0;
	lenmax = 0;
	while (i < renderer_getraymax())
	{
		ray = renderer_getray(i);
		if (ray->length != INFINITY && ray->length > lenmax)
			lenmax = ray->length;
		i++;
	}
	return (lenmax);
}

void				print_obj_hit_color_length_mode(void)
{
	int				x;
	int				y;
	t_ray			*ray;
	float			multvalue;
	float			max_len;
	t_rgb			color;

	y = 0;
	max_len = get_max_raylen();
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			ray = renderer_getray(x + y * win_getx());
			if (ray->length != INFINITY)
			{
				multvalue = 1 - ray->length / max_len;
				color = ray->obj_hit->color.rgb;
				color.r = color.r * multvalue;
				color.g = color.g * multvalue;
				color.b = color.b * multvalue;
				mlx_px_to_img(env_get()->win->img, x, y, rgb_to_int(color));
			}
			else
				mlx_px_to_img(env_get()->win->img, x, y, 0);
			x++;
		}
		y++;
	}
}

void				print_final_ray_color_mode(void)
{
	int				x;
	int				y;
	t_ray			*ray;

	y = 0;
	while (y < win_gety())
	{
		x = 0;
		while (x < win_getx())
		{
			ray = renderer_getray(x + y * win_getx());
			mlx_px_to_img(env_get()->win->img, x, y, ray->color.rgb.value);
			x++;
		}
		y++;
	}
}

void				print_cursor_over_image(void)
{
	if (cursor_mode_get() == 1)
		mlx_px_to_img(env_get()->win->img, cursor_getx(), cursor_gety(), 0xff0000);
}

void				printing(void)
{
	if (print_mode_get() == OBJ_HIT_MODE)
		print_obj_hit_color_mode();
	else if (print_mode_get() == OBJ_HIT_LENGTH_MODE)
		print_obj_hit_color_length_mode();
	else if (print_mode_get() == RAY_COLOR_MODE)
		print_final_ray_color_mode();
	print_cursor_over_image();
	mlx_put_image_to_window(mlx_get(), win_get()->winptr, win_get()->img->imgptr, 0, 0);
}
