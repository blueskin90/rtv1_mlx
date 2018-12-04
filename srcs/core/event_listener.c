/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_listener.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 17:36:18 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/04 06:52:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	switch_printmode(void)
{
	if (print_mode_get() == MODE_MAX)
		print_mode_set(0);
	else
		print_mode_set(print_mode_get() + 1);
}

int		key_pressed(int key)
{
	if (key == X_KEY_ESCAPE)
	{
		//freeenv(env);
		exit(EXIT_SUCCESS);
	}
	if (cursor_mode_get() == 0)
	{
		if (key == X_KEY_SPACE)
			switch_printmode();
	}
	if (key == X_KEY_L_SHIFT)
		cursor_mode_toggle();
	if (cursor_mode_get() == 1)
	{
		if (key == X_KEY_R)
			cursor_reset();
		if (key == X_KEY_SPACE)
		{
			print_lights(scene_get());
			display_cursor_infos();
		}
		if (key == X_KEY_L_ARROW)
			cursor_movex(-1);
		if (key == X_KEY_R_ARROW)
			cursor_movex(1);
		if (key == X_KEY_U_ARROW)
			cursor_movey(-1);
		if (key == X_KEY_D_ARROW)
			cursor_movey(1);
	}

	printing();	
	return 0;
}

int		mouse_move(int x, int y)
{
	static int		oldx = INT_MAX;
	static int		oldy = INT_MAX;

	if (oldx != INT_MAX && cursor_mode_get() == 1)
	{
		cursor_movex(x - oldx);
		cursor_movey(y - oldy);
	}
	oldx = x;
	oldy = y;
	printing();
	return (1);
}

void		events_listener(t_env *env)
{
//	mlx_hook(env->win, 2, 0, key, env);
	mlx_hook(env->win->winptr, X_MOTIONNOTIFY, 0, mouse_move, env); 
	mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, key_pressed, env);
//	mlx_hook(env->win, X_MOTIONNOTIFY, X_POINTERMOTION_MASK, (int (*)(int, int, void *))pos_notify, env);
}
