/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 20:50:43 by nfinkel           #+#    #+#             */
/*   Updated: 2018/11/05 18:57:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

void	pos_notify(int x, int y, t_env *env)
{
//	ft_printf("------------------\n");
//	ft_printf("x : %d y : %d\n", x, y);
//	ft_printf("xx : %d yy : %d\n", cam_to_world_x((double)x, env), 
//			cam_to_world_y((double)y, env));
//	ft_printf("------------------\n");
}

void	key(int key, t_env *env)
{
	if (key == X_KEY_ESCAPE)
		terminate(env);
}

void		events_listener(t_env env)
{
	mlx_hook(env.mlx->win[0], X_KEYPRESS, 0, (int (*)(int, void *))key, &env);
	mlx_hook(env.mlx->win[0], X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, &env);
}
