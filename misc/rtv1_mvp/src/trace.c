/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/05 17:21:28 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

static const t_f	g_f[] =
{
	in_sphere,
};

double	intersection_distance(t_env env, t_v3 *raydir, t_v3 *rayorig, int *obj_index)
{
	int		i;
	double	dist;
	double	near;

	near = INFINITY;
	i = 0;
	while (env.objs[i])
	{
		if ((dist = g_f[env.objs[i]->type](raydir, rayorig, env.objs[i])))
		{
			if (dist > 0 && dist < near)
			{
				near = dist;
				*obj_index = i;
			}
		}
		i++;
	}
	return (near);
}

void	trace(t_env env, t_v3 *ray, int x, int y)
{
	double			near;
	int				obj_index;
	unsigned int	color;

	obj_index = -1;
	near = intersection_distance(env, ray, &env.cam->pt, &obj_index);
	if (near != INFINITY && obj_index >= 0)
	{
	
	//	ft_printf("near : %f\n", near);
		color = colorization(env, ray, near, obj_index);
//		color = 0xffffff;
		ftx_buffpixel(env.mlx->img[0], x, y,color);
//		printf("near : %f obj index : %d \n", near, obj_index);
	}
}
