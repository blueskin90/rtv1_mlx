/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 00:26:39 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 05:03:22 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			verbose_args(void)
{
	print_args();
	return;
}

void			verbose_init(void)
{
	
	print_env();
	return;
}

void			verbose_parsing(void)
{
	printf("/!\\ == Verbose for parsing == /!\\\n\n");
	print_scenes(env_get()->scene);
	printf("\n==== end of parsing verbose ====\n\n");
	return;
}

void			verbose_settings(void)
{
	printf("/!\\ == Verbose for settings == /!\\\n\n");
	print_settings();
	printf("\n==== end of settings verbose ====\n\n");
	return;
}

void			verbose_running(void)
{
	printf("/!\\ == Verbose for running == /!\\\n\n");
	print_running();
	printf("\n==== end of running verbose ====\n\n");
	return;
}

void			verbose_bad_stepvalue(int step)
{
	ft_putstr_fd("Verbose got a step value that does not exists : ", 2);
	ft_putnbr_fd(step, 2);
	ft_error("\n");
	return;
}



void			print_verbose(int step)
{
	if (step == ARGS_PARSING)
		verbose_args();
	else if (step == INIT)
		verbose_init();
	else if (step == PARSING)
		verbose_parsing();
	else if (step == SETTINGS)
		verbose_settings();
	else if (step == RUNNING)
		verbose_running();
	else
		verbose_bad_stepvalue(step);
}

void			verbose()
{
	if (verbose_mode_get() == ALL_VERBOSE || verbose_mode_get() == step_get())
		print_verbose(step_get());
	return;
}
