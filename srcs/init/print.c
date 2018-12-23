/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 03:47:05 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 05:11:27 by toliver          ###   ########.fr       */
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

void			print_img(t_img *img)
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
		print_img(win->img);
	}	
}

void				print_scenes(t_scene *scene)
{
	if (scene == NULL)
	{
		printf("	No scene at the moment\n");
		return ;
	}
	printf("	== /!\\ PRINTING SCENES /!\\ ==\n");
	while (scene)
	{
		printf("		name : %s\n", scene->name);
	//	print_objects(scene->objs);
	//	print_lights(scene->lights);
	//	print_cameras(scene->cameras);
		scene = scene->next;
	}
}

void			print_env()
{
	t_env		*env;

	env = env_get();
	printf("/!\\ == Verbose for env === /!\\\n\n");
	print_mlx(env->mlx);
	print_window(env->win);
	print_scenes(env->scene);
	printf("\n===== end of env verbose ======\n\n");
}
