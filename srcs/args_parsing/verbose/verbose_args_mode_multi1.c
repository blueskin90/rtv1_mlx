/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_args_mode_multi1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:29:47 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 03:30:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static char		*renderer_mode_string(int mode)
{
	if (mode == STACK)
		return ("STACK");
	if (mode == MALLOC)
		return ("MALLOC");
	if (mode == MULTITHREAD)
		return ("MULTITHREAD");
	if (mode == GRAPHIQUE)
		return ("GRAPHIQUE");
	if (mode == CLUSTERING)
		return ("CLUSTERING");
	return ("ERROR, BAD RENDERER MODE !\n");
}

void			print_renderer_mode(int mode)
{
	char		*value;

	if (mode == NO_RENDERER)
		ft_printf("	No rendering will be done !\n");
	if (mode >= MAX_RENDERER_MODE)
		ft_printf("	Renderer mode is higher than the max !\n");
	else
	{
		value = renderer_mode_string(mode);
		ft_printf("	Renderer mode is : %s\n", value);
	}
}
