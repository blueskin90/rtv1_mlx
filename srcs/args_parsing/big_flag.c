/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 00:07:38 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 17:45:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_parsing.h"

void			parse_bigflag_default_value(char *flagvalue, t_args *args)
{
	if (strcmp(flagvalue, "print") == 0)
		args->print_mode = MAX_PRINT_MODE;
	else if (strcmp(flagvalue, "verbose") == 0)
		args->verbose_mode = ALL_VERBOSE;
	else
		print_usage();
}

void			parse_bigflag_given_value(char *flagvalue, t_args *args)
{
	if (ft_strcmp(flagvalue, "print") == '=')
		parse_print_mode(flagvalue, args);
	else if (ft_strcmp(flagvalue, "verbose") == '=')
		parse_verbose_mode(flagvalue, args);
	else if (ft_strcmp(flagvalue, "renderer") == '=')
		parse_renderer_mode(flagvalue, args);
	else
		print_usage();
}

void			parse_bigflag(char *flagvalue, t_args *args)
{
	if (ft_strchr(flagvalue, '=') == NULL)
		parse_bigflag_default_value(flagvalue, args);
	else
		parse_bigflag_given_value(flagvalue, args);
}
