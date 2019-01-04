/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:42:05 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 01:22:53 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					key_pressed(int key, t_env *env)
{
	(void)env;
	if (key == X_KEY_ESCAPE)
	{
		//freeenv(env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void				loop(t_args *args, t_env *env)
{
	//	step_set(LOOP);
	if (args->print_mode != NO_PRINT && args->renderer_mode != NO_RENDERER)
	{
		mlx_hook(env->win->winptr, X_KEYPRESS, X_KEYPRESS_MASK, key_pressed,
				env);
		mlx_loop(env->mlx);
	}
	if (args->verbose_mode == LOOP || args->verbose_mode == ALL_VERBOSE)
		verbose_loop(args, env);
}
