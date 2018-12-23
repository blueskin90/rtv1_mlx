/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 23:54:09 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 03:05:52 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_parsing.h"

void			print_usage(void)
{
	ft_error(USAGE);
}

void			print_render_usage(void)
{
	ft_putstr_fd("rtv1: --render param incorrect, it can be :\n", 2);
	ft_putstr_fd("		--render : full options raytracing\n", 2);
	ft_putstr_fd("		--render=VALUE : VALUE can be :\n", 2);
	ft_putstr_fd("			0 : no render\n", 2);
	ft_putstr_fd("			1 : render hit color mode\n", 2);
	ft_putstr_fd("			2 : render depth color mode\n", 2);
	ft_putstr_fd("			3 : render full options raytracing\n", 2);
	ft_putstr_fd("			4 : render test options raytracing\n", 2);
//	ft_putstr_fd("			5 : launch editor\n", 2);
	ft_error(NULL);
}

void			print_verbose_usage(void)
{
	ft_putstr_fd("rtv1: --verbose param incorrect, it can be :\n", 2);
	ft_putstr_fd("		--verbose : standard verbose on everything\n", 2);
	ft_putstr_fd("		--verbose=VALUE : VALUE can be :\n", 2);
	ft_putstr_fd("			0 : no verbose\n", 2);
	ft_putstr_fd("			1 : verbose on args_parsing\n", 2);
	ft_putstr_fd("			2 : verbose on init\n", 2);
	ft_putstr_fd("			3 : verbose on parsing\n", 2);
	ft_putstr_fd("			4 : verbose on settings\n", 2);
	ft_putstr_fd("			5 : verbose on running\n", 2);
	ft_putstr_fd("			6 : all of the above\n", 2);
	ft_error(NULL);
}

void			print_renderer_usage(void)
{
	ft_putstr_fd("rtv1: --renderer=VALUE param incorrect, VALUE can be :\n", 2);
	ft_putstr_fd("			0 : stack\n", 2);
	ft_putstr_fd("			1 : malloc\n", 2);
//	ft_putstr_fd("			2 : multithread\n", 2);
//	ft_putstr_fd("			3 : graphique\n", 2);
//	ft_putstr_fd("			4 : clustering\n", 2);
	ft_error(NULL);
}
