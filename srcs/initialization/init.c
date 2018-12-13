/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 16:37:52 by toliver           #+#    #+#             */
/*   Updated: 2018/12/13 15:05:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_img				*img_init(int width, int height, void *mlx)
{
	t_img			*img;

	img = (t_img*)ft_malloc(sizeof(t_img));
	img->width = width;
	img->height = height;
	img->imgptr = mlx_new_image(mlx, width, height);
	if (!(img->img_str = mlx_get_data_addr(img->imgptr, &img->bpp, &img->sl, &img->endian)))
		ft_error(MLX_IMG_FAIL);
	return (img);
}

t_win				*win_init(int width, int height, char *name, void *mlx)
{
	t_win			*win;

	win = (t_win*)ft_malloc(sizeof(t_win));
	win->winx = width;
	win->winy = height;
	if (!(win->winptr = mlx_new_window(mlx, width, height, name)))
		return (NULL);
	if (!(win->img = img_init(width, height, mlx)))
		ft_error(MLX_IMG_FAIL);
	return (win);
}

t_env				*env_init(void)
{
	t_env			*env;

	env = (t_env*)ft_malloc(sizeof(t_env));
	if (!(env->mlx = mlx_init()))
		ft_error(MLX_FAIL);
	if (!(env->win = win_init(WIN_WIDTH, WIN_HEIGHT, "RTv1",env->mlx)))
		ft_error(WINDOW_FAIL);
	env->scene = NULL;
	return (env);
}

int					init(void)
{
	env_set(env_init());
	return (1);
}
