/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 14:09:35 by cvermand          #+#    #+#             */
/*   Updated: 2018/06/24 17:27:49 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

double		cam_to_world_x(double x, t_env *env)
{
	return ((2.0 * (((double)x + 0.5) * env->invWidth) - 1) 
			* env->cam->angle * env->cam->ratio_x);
}

double		cam_to_world_y(double y, t_env *env)
{
	return ((1.0 - 2.0 * (((double)y + 0.5) * env->invHeight)) * env->cam->angle 
			* env->cam->ratio_y);
}

double		world_to_cam_x(double xx, t_env *env)
{
	return (((xx / (env->cam->angle * env->cam->ratio_x) + 1) * 0.5 * env->width) - 0.5);
}

double		world_to_cam_y(double yy, t_env *env)
{
	return (((yy / env->cam->angle * env->cam->ratio_y - 1) * -0.5 * env->height) - 0.5);
}
