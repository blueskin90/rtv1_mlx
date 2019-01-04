/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:25 by toliver           #+#    #+#             */
/*   Updated: 2019/01/05 00:14:48 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			verbose_args(t_args *args)
{
	ft_printf("\n/!\\ == Verbose for args == /!\\\n\n");
	print_renderer_mode(args->renderer_mode);
	print_args_files(args->files);
	print_print_mode(args->print_mode);
	print_verbose_mode(args->verbose_mode);
	print_debug_mode(args->debug_mode);
	ft_printf("===== end of args verbose =====\n\n");
}
