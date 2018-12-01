/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/01 09:43:50 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		key_pressed(int key)
{
	if (key == X_KEY_ESCAPE)
	{
		//freeenv(env);
		exit(EXIT_SUCCESS);
	}
	return 0;
}

void		events_listener(t_env *env)
{
//	mlx_hook(env->win, 2, 0, key, env);
//	mlx_hook(env->win->winptr, X_MOTIONNOTIFY, 0, mousemove, env); 
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, key_pressed, env);
//	mlx_hook(env->win, X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, env);
}
