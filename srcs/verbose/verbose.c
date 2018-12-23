/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 00:26:39 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 02:39:33 by toliver          ###   ########.fr       */
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
//	print_env();
	return;
}

void			verbose_parsing(void)
{
//	print_parsing();
	return;
}

void			verbose_settings(void)
{
//	print_settings();
	return;
}

void			verbose_running(void)
{
//	print_running();
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
