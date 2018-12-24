/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 23:54:09 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 03:37:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_parsing.h"

void			print_usage(void)
{
	ft_error(USAGE);
}

void			print_print_usage(void)
{
	ft_putstr_fd("rtv1: --print param incorrect, it can be :\n", 2);
	ft_putstr_fd("		--print : switchable full options raytracing\n", 2);
	ft_putstr_fd("		--print=VALUE : VALUE can be :\n", 2);
	ft_putstr_fd("			0 : no print\n", 2);
	ft_putstr_fd("			1 : print hit color mode\n", 2);
	ft_putstr_fd("			2 : print depth color mode\n", 2);
	ft_putstr_fd("			3 : print full options raytracing\n", 2);
	ft_putstr_fd("			4 : print test options raytracing\n", 2);
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
	ft_putstr_fd("			0 : no rendering\n", 2);
	ft_putstr_fd("			1 : stack\n", 2);
	ft_putstr_fd("			2 : malloc\n", 2);
	ft_error(NULL);
}

/*
**  rajouter au fur et a mesure dans la fonction precedente
**	ft_putstr_fd("			3 : multithread\n", 2);
**	ft_putstr_fd("			4 : graphique\n", 2);
**	ft_putstr_fd("			5 : clustering\n", 2);
*/
