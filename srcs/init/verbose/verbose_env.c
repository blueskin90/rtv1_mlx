/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:51:56 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 21:06:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_mlx(void *mlx)
{
	if (!mlx)
		ft_printf("	No MLX pointer allocated\n");
	else
		ft_printf("	MLX ptr = %p\n", mlx);
}

void			print_mlximg(t_img *img)
{
	if (!img)
	{
		ft_printf("		No IMG structure allocated\n");
		return ;
	}
	ft_printf("		img size is %d x %d\n", img->width, img->height);
	ft_printf("		img ptr = %p\n", img->imgptr);
	ft_printf("		img_str ptr = %p\n", img->img_str);
	ft_printf("		img bpp = %d\n", img->bpp);
	ft_printf("		img sl = %d\n", img->sl);
	ft_printf("		img endian = %d\n", img->endian);
}

void			print_window(t_win *win)
{
	if (!win)
		ft_printf("	No WINDOW structure allocated\n");
	else
	{
		ft_printf("	Window size is %d x %d\n", win->winx, win->winy);
		ft_printf("	winptr = %p\n", win->winptr);
		print_mlximg(win->img);
	}
}

void			verbose_env(t_env *env)
{
	ft_printf("/!\\ == Verbose for env === /!\\\n\n");
	print_mlx(env->mlx);
	print_window(env->win);
	print_scenes(env->scene);
	ft_printf("\n===== end of env verbose ======\n\n");
}
