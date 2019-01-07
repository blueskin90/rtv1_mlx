/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 00:42:05 by toliver           #+#    #+#             */
/*   Updated: 2019/01/07 16:35:58 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					key_pressed(int key, t_env *env)
{
	if (key == X_KEY_ESCAPE)
	{
		free_env(env);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int					window_closed(t_env *env)
{
	ft_putstr_fd("Espece de barbare, go utiliser echap !\n", 2);
	free_env(env);
	exit(EXIT_SUCCESS);
	return (0);
}

void				loop(t_args *args, t_env *env)
{
	env->args = args;
	if (args->print_mode != NO_PRINT && args->renderer_mode != NO_RENDERER)
	{
		mlx_hook(env->win->winptr, 2, 0, key_pressed, env);
		mlx_hook(env->win->winptr, 17, 0, window_closed, env);
		if (args->verbose_mode == LOOP || args->verbose_mode == ALL_VERBOSE)
			verbose_loop(args, env);
		mlx_loop(env->mlx);
	}
	free_env(env);
}
