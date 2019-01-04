/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_args_mode_bool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:24:51 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 17:46:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_debug_mode(int mode)
{
	char		*value;

	value = (mode == 1 ? "ON" : "OFF");
	ft_printf("	Debug mode is %s\n", mode);
}
