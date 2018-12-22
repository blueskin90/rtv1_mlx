/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:18:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 00:41:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_PARSING_H
# define ARGS_PARSING_H

#include "libft.h"
#include "rtv1_struct.h"
#include <stdio.h>

#define PROGRAM_NAME "./rtv1"

#define SHORT_FLAGS "dp"
#define LONG_FLAGS "render;verbose"

# define USAGE "usage: rtv1 [-dp] [--render[=RENDER_MODE]] [--verbose[=VERBOSE_MODE]] [file]\n"

/*
** USAGE FUNCTIONS
*/

void				print_usage(void);
void				print_render_usage(void);
void				print_verbose_usage(void);

/*
** PARSING FUNCTIONS
*/

void				parse_arguments(int ac, char **av, t_args *args);
void				parse_smallflag(char *flagvalue, t_args *args);
void				parse_bigflag(char *flagvalue, t_args *args);
void				parse_bigflag_given_value(char *flagvalue, t_args *args);
void				parse_bigflag_default_value(char *flagvalue, t_args *args);
void				parse_verbose_mode(char *flagvalue, t_args *args);
void				parse_render_mode(char *flagvalue, t_args *args);

# endif
