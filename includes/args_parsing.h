/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:18:49 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 17:52:36 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_PARSING_H
# define ARGS_PARSING_H

#include "libft.h"
#include "rtv1_struct.h"

#define PROGRAM_NAME "./rtv1"
#define SHORT_FLAGS "d"
#define LONG_FLAGS "print;verbose;renderer"


/*
** USAGE FUNCTIONS
*/

void				print_usage(void);
void				print_print_usage(void);
void				print_verbose_usage(void);
void				print_renderer_usage(void);

/*
** PARSING FUNCTIONS
*/

void				parse_flags_check(t_args *args);
void				parse_arguments(int ac, char **av, t_args *args);
void				parse_smallflag(char *flagvalue, t_args *args);
void				parse_bigflag(char *flagvalue, t_args *args);
void				parse_bigflag_given_value(char *flagvalue, t_args *args);
void				parse_bigflag_default_value(char *flagvalue, t_args *args);
void				parse_verbose_mode(char *flagvalue, t_args *args);
void				parse_render_mode(char *flagvalue, t_args *args);
void				parse_renderer_mode(char *flagvalue, t_args *args);
void				parse_print_mode(char *flagvalue, t_args *args);

# endif
