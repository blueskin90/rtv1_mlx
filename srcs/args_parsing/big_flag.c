/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_flag.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 00:07:38 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 03:08:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_parsing.h"

void			parse_bigflag_default_value(char *flagvalue, t_args *args)
{
	if (strcmp(flagvalue, "render") == 0)
		args->render_mode = TOTAL_COLOR;
	else if (strcmp(flagvalue, "verbose") == 0)
		args->verbose_mode = ALL_VERBOSE;
	else
		print_usage();
}

void			parse_render_mode(char *flagvalue, t_args *args)
{
	char		*value;
	int			final_val;

	final_val = -1;
	value = ft_strchr(flagvalue, '=') + 1;
	if (value[0] < '0' || value[0] > '9' || value[1]
			|| (final_val = ft_atoi(value)) >= MAX_RENDER_MODE)
		print_render_usage();
	args->render_mode = final_val;
}

void			parse_verbose_mode(char *flagvalue, t_args *args)
{
	char		*value;
	int			final_val;

	final_val = -1;
	value = ft_strchr(flagvalue, '=') + 1;
	if (value[0] < '0' || value[0] > '9' || value[1]
			|| (final_val = ft_atoi(value)) >= MAX_VERBOSE_MODE)
		print_verbose_usage();
	args->verbose_mode = final_val;
}

void			parse_renderer_mode(char *flagvalue, t_args *args)
{
	char		*value;
	int			final_val;

	final_val = -1;
	value = ft_strchr(flagvalue, '=') + 1;
	if (value[0] < '0' || value[0] > '9' || value[1]
			|| (final_val = ft_atoi(value)) >= MAX_RENDERER_MODE)
		print_renderer_usage();
	args->renderer_mode = final_val;
}

void			parse_bigflag_given_value(char *flagvalue, t_args *args)
{
	if (ft_strcmp(flagvalue, "render") == '=')
		parse_render_mode(flagvalue, args);
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
