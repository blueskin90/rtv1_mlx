/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/10 19:43:52 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	pos_notify(int x, int y, t_env *env)
{
	printf("------------------\n");
	printf("x : %d y : %d\n", x, y);
///	ft_printf("xx : %d yy : %d\n", cam_to_world_x((double)x, env), 
//			cam_to_world_y((double)y, env));
	printf("------------------\n");
}

int		key(int key, t_env *env)
{
	// FREE ICI 
	if (key == X_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	return 0;
}

void		events_listener(t_env *env)
{
	printf("%d", X_KEYPRESS);
//	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, (int (*)(int, void *))key, env);
//	mlx_hook(env->win, X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, env);

}
