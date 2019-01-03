/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_types_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:05:58 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 21:50:15 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		check_float_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "ambiant") ||
			!compare(key, "radius") ||
			!compare(key, "roll") ||
			!compare(key, "intensity") ||
			!compare(key, "brillance") ||
			!compare(key, "fov") ||
			!compare(key, "r") ||
			!compare(key, "g") ||
			!compare(key, "b") ||
			!compare(key, "x") ||
			!compare(key, "y") ||
			!compare(key, "z") ||
			!compare(key, "angle"))
		return (1);
	wrong_format(key, FLOAT);
	return (0);
}

int		check_int_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "r") ||
			!compare(key, "g") ||
			!compare(key, "fov") ||
			!compare(key, "intensity") ||
			!compare(key, "brillance") ||
			!compare(key, "x") ||
			!compare(key, "y") ||
			!compare(key, "z") ||
			!compare(key, "roll") ||
			!compare(key, "b"))
		return (1);
	wrong_format(key, INTEGER);
	return (0);
}
