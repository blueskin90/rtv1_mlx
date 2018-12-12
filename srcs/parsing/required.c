/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   required.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:35:23 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 14:17:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		required_float(float number, bool required, char *error)
{
	if (number == INFINITY && required)
		is_required(error, false);
	return (number);
}

t_vec		required_vec(t_vec vec, bool required, char *error)
{
	if (min_of_vec(vec) == INFINITY && required)
		is_required(error, false);
	return (vec);
}
