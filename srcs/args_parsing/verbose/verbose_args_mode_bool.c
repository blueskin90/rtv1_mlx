/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_args_mode_bool.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:24:51 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 03:26:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			print_debug_mode(int mode)
{
	char		*value;

	value = (mode == 1 ? "ON" : "OFF");
	ft_printf("	Debug mode is %s\n", mode);
}

void			print_parse_mode(int mode)
{
	char		*value;

	value = (mode == 0) ? "STANDARD" : "JSON";
	ft_printf("	Parsing mode is : %s\n", value);
}
