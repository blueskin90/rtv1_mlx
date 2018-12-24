/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 16:56:51 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/23 19:47:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					wrong_format(char *form, e_type type)
{
	ft_putstr_fd(X_BAD_FORMAT, 2);
	ft_putstr_fd(form, 2);
	ft_putstr_fd(X_SHOULD_NOT_BE, 2);
	if (type == INTEGER)
		ft_putstr_fd("INTEGER\n", 2);
	else if (type == STRING)
		ft_putstr_fd("STRING\n", 2);
	else if (type == FLOAT)
		ft_putstr_fd("FLOAT\n", 2);
	else if (type == BOOL)
		ft_putstr_fd("BOOL\n", 2);
	else if (type == OBJECT)
		ft_putstr_fd("OBJECT\n", 2);
	else if (type == NULL_ELEM)
		ft_putstr_fd("NULL_ELEM\n", 2);
	else if (type == ARRAY)
		ft_putstr_fd("ARRAY\n", 2);
	exit(0);
}

void					is_required(char *key, bool one)
{
	if (one)
		ft_putstr_fd(AT_LEAST_ONE_REQUIRED, 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(IS_REQUIRED, 2);
	exit(0);
}
