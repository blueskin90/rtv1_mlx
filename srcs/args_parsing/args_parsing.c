/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 18:50:27 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 00:41:34 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "args_parsing.h"

t_args			*args_init(void)
{
	t_args		*args;

	args = (t_args*)ft_malloc(sizeof(t_args));
	args->parse_mode = 0;
	args->verbose_mode = 0;
	args->render_mode = 0;
	args->debug_mode = 0;
	args->files = NULL;
	return (args);
}

void			args_parsing(int ac, char **av)
{
	t_args		*args;

	args = args_init();
	parse_arguments(ac, av, args);
	step_set(ARGS_PARSING);
	args_set(args);
	verbose();
}
