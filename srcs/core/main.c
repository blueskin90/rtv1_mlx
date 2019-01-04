/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:32:23 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 01:11:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				main(int ac, char **av)
{
	t_args		*args;
	t_env		*env;

	args = args_parsing(ac, av);
	env = init(args);
	env->scene = parsing(args);
	settings(args, env);
	running(args, env->scene);
	printing(args, env->scene, env->win, env->mlx);
	loop(args, env);
	return (1);
}
