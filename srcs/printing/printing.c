/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 09:50:16 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 19:46:39 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_stack_raytracer(t_scene *scenes, t_win *win,
		void *mlx)
{
	mlx_put_image_to_window(mlx, win->winptr,
			scenes->cameras->params.camera.renderer->img->imgptr, 0, 0);
}

void				print_malloc_raytracer(t_scene *scenes, t_win *win,
		void *mlx)
{
	int				x;
	int				y;
	int				i;
	t_renderer		*renderer;

	i = 0;
	renderer = scenes->cameras->params.camera.renderer;
	y = 0;
	while (y < renderer->height)
	{
		x = 0;
		while (x < renderer->width)
		{
			mlx_px_to_img(renderer->img, x, y,
					renderer->renderer[i].color.value);
			i++;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx, win->winptr, renderer->img->imgptr, 0, 0);
}

void				printing(t_args *args, t_scene *scenes, t_win *win,
		void *mlx)
{
//	step_set(PRINTING);
	if (args->print_mode != NO_PRINT && args->renderer_mode != NO_RENDERER)
	{
		if (args->renderer_mode == STACK)
			print_stack_raytracer(scenes, win, mlx);
		else if (args->renderer_mode == MALLOC)
			print_malloc_raytracer(scenes, win, mlx);
		else
			ft_printf("wrong renderer_mode !\n");
	}
	if (args->verbose_mode == PRINTING || args->verbose_mode == ALL_VERBOSE)
		verbose_printing(args, scenes);
	if (args->print_mode != NO_PRINT && args->renderer_mode != NO_RENDERER)
		mlx_loop(mlx);
}
