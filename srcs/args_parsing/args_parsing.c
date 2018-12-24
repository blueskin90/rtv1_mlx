/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:50:27 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 06:19:48 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "args_parsing.h"

t_args			*args_init(void)
{
	t_args		*args;

	args = (t_args*)ft_malloc(sizeof(t_args));
	args->parse_mode = STANDARD;
	args->verbose_mode = NO_VERBOSE;
	args->print_mode = TOTAL_COLOR;
	args->debug_mode = 0;
	args->renderer_mode = MALLOC;
	args->files = NULL;
	return (args);
}

t_args			*args_parsing(int ac, char **av)
{
	t_args		*args;

//	step_set(ARGS_PARSING);
	args = args_init();
//	args_set(args);
	parse_arguments(ac, av, args);
	if (args->verbose_mode == ARGS_PARSING || args->verbose_mode == ALL_VERBOSE)
		verbose_args(args);
	return (args);
}
