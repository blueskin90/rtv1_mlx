/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:51:56 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 04:17:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_mlx(void *mlx)
{
	if (!mlx)
		printf("	No MLX pointer allocated\n");
	else
		printf("	MLX ptr = %p\n", mlx);
}

void			print_mlximg(t_img *img)
{
	if (!img)
	{
		printf("		No IMG structure allocated\n");
		return ;
	}
	printf("		img size is %d x %d\n", img->width, img->height);
	printf("		img ptr = %p\n", img->imgptr);
	printf("		img_str ptr = %p\n", img->img_str);
	printf("		img bpp = %d\n", img->bpp);
	printf("		img sl = %d\n", img->sl);
	printf("		img endian = %d\n", img->endian);
}

void			print_window(t_win *win)
{
	if (!win)
		printf("	No WINDOW structure allocated\n");
	else
	{
		printf("	Window size is %d x %d\n", win->winx, win->winy);
		printf("	winptr = %p\n", win->winptr);
		print_mlximg(win->img);
	}	
}

void			verbose_env(t_env *env)
{
	printf("/!\\ == Verbose for env === /!\\\n\n");
	print_mlx(env->mlx);
	print_window(env->win);
//	print_scenes(env->scene);
	printf("\n===== end of env verbose ======\n\n");
}
