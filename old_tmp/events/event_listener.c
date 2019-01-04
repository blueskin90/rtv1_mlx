/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 00:54:09 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			key_pressed(int key)
{
	if (key == X_KEY_ESCAPE)
	{
		//freeenv(env);
		exit(EXIT_SUCCESS);
	}
	printing();
	return (0);
}

void		events_listener(void)
{
	t_env	*env;

	env = env_get();
	//	mlx_hook(env->win, 2, 0, key, env);
	//	mlx_hook(env->win->winptr, X_MOTIONNOTIFY, 0, mouse_move, env);
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, key_pressed, env);
}
