/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:23:47 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 22:41:32 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			main(void)
{
	t_env		env;
	int			x;
	int			y;
	t_matrix	m;
	t_proj		*p;
	t_vertex	v;
	t_vector	vec;
	double		distance;
	int			pos;

	if (!(init_env(&env)))
		safe_error_exit(&env, "Env init went wrong");
	p = create_projection_struct(ft_to_radians(90), 1.5, 0, 100);
	init_projection(p , &m);
	y = 0;
	while (y < env.scr.height)
	{
		x = 0;
		while (x < env.scr.width)
		{
			init_vertex(x, y, 1, &v);
			init_vector(&vec, &v, NULL);
			if ((distance = in_sphere(&vec)))
			{
				init_scale(distance, &m);
				matrix_multiplication(&m, &v);	
				pos = get_pixel_index(x, y);
				if (pos >= 0 && pos < env.scr.width * env.scr.height)
					env.data_addr[pos] = 0xffffff;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env.mlx, env.win, env.img, 0, 0);
	mlx_loop(env.mlx);

	return (0);
}
