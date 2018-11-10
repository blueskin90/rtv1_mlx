/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:58:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/10 01:28:21 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

void		render(t_env env)
{
	int		x;
	double	xx;
	int		y;
	double	yy;
	t_v3	ray;
	y = -1;
	while (++y < env.height && (x = -1))
	{
		yy = cam_to_world_y((double) y, &env);
		while (++x < env.width)
		{
			xx = cam_to_world_x((double)x, &env);
			ray = ft_v3new(xx, yy, 1);
			ft_v3norm(&ray);
			trace(env, &ray, x, y);
		}
	}
/*	dprintf(1,"lowest : %f \n highest : %f \n medium : %f\n total : %f\n ", 
			env.low_light, 
			env.high_light,
			env.total_light / env.nbr_light,
			env.total_light);*/
	ftx_showimg(env.mlx, 0, 0);
}
