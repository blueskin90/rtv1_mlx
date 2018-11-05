/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:24:41 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 20:17:24 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	init_env(t_env *env)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN, "Fractol");
	env->img = mlx_new_image(env->mlx, WIDTH_SCREEN, HEIGHT_SCREEN);
	if (!(env->data_addr = (unsigned int*)mlx_get_data_addr(env->img,
			&env->bits_per_pixel, &env->bytes_per_line, &env->endian)))
		return (0);
	env->scr.width = WIDTH_SCREEN;
	env->scr.height = HEIGHT_SCREEN;
	env->scr.zoom = 0.4;
	get_screen_ratio(&env->scr);
	env->scr.half_width = env->scr.width / 2;
	env->scr.half_height = env->scr.height / 2;
	return (1);
}
