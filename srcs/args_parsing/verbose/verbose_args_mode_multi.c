/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_args_mode_multi.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:28:10 by toliver           #+#    #+#             */
/*   Updated: 2019/01/05 00:12:14 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char		*print_mode_string(int mode)
{
	if (mode == HIT_COLOR)
		return ("HIT_COLOR");
	if (mode == DEPTH_COLOR)
		return ("DEPTH_COLOR");
	if (mode == TOTAL_COLOR)
		return ("TOTAL_COLOR");
	return ("ERROR, BAD RENDER MODE !\n");
}

void			print_print_mode(int mode)
{
	char		*value;

	value = NULL;
	if (mode == NO_PRINT)
		ft_printf("	No PRINTING will be done\n");
	else if (mode >= MAX_PRINT_MODE)
		ft_printf("	PRINT mode is higher than mode max !\n");
	else
	{
		value = print_mode_string(mode);
		ft_printf("	PRINT mode is : %s\n", print_mode_string(mode));
	}
}

static char		*verbose_mode_string(int mode)
{
	if (mode == ARGS_PARSING)
		return ("ARGS_PARSING");
	if (mode == INIT)
		return ("INIT");
	if (mode == PARSING)
		return ("PARSING");
	if (mode == SETTINGS)
		return ("SETTINGS");
	if (mode == RUNNING)
		return ("RUNNING");
	if (mode == PRINTING)
		return ("PRINTING");
	if (mode == LOOP)
		return ("LOOP");
	return ("ERROR, BAD VERBOSE MODE !\n");
}

void			print_verbose_mode(int mode)
{
	char		*value;

	value = NULL;
	if (mode == NO_VERBOSE)
		ft_printf("	Verbose is OFF (should be impossible)\n");
	else if (mode >= MAX_VERBOSE_MODE)
		ft_printf("	Verbose is higher than verbose max !\n");
	else if (mode == ALL_VERBOSE)
		ft_printf("	Verbose is ON for all steps\n");
	else
	{
		value = verbose_mode_string(mode);
		ft_printf("	Verbose is ON for %s\n", value);
	}
}
