/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_types_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 21:05:19 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 22:00:45 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		check_array_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "parent_element") ||
			!compare(key, "spheres") ||
			!compare(key, "cylinders") ||
			!compare(key, "planes") ||
			!compare(key, "cones") ||
			!compare(key, "cameras") ||
			!compare(key, "lights"))
		return (1);
	wrong_format(key, ARRAY);
	return (0);
}

static int		check_object_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "translation") ||
			!compare(key, "scene") ||
			!compare(key, "objects") ||
			!compare(key, "object") ||
			!compare(key, "light") ||
			!compare(key, "camera") ||
			!compare(key, "rotation") ||
			!compare(key, "direction") ||
			!compare(key, "position") ||
			!compare(key, "rotation") ||
			!compare(key, "color") ||
			!compare(key, "lookat"))
		return (1);
	wrong_format(key, OBJECT);
	return (0);
}

static int		check_string_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (!compare(key, "name") ||
			!compare(key, "hex"))
		return (1);
	wrong_format(key, STRING);
	return (0);
}

static int		check_null_keys(char *key)
{
	int		(*compare)(const char *, const char *);

	compare = &ft_strcmp;
	if (			!compare(key, "ambiant") ||
			!compare(key, "radius") ||
			!compare(key, "x") ||
			!compare(key, "y") ||
			!compare(key, "z") ||
			!compare(key, "r") ||
			!compare(key, "g") ||
			!compare(key, "b"))
		return (1);
	wrong_format(key, NULL_ELEM);
	return (0);
}

int				check_type_of_key(char *key, t_json_data type)
{
	if (type == FLOAT)
		return (check_float_keys(key));
	else if (type == OBJECT)
		return (check_object_keys(key));
	else if (type == ARRAY)
		return (check_array_keys(key));
	else if (type == INTEGER)
		return (check_int_keys(key));
	else if (type == NULL_ELEM)
		return (check_null_keys(key));
	else if (type == STRING)
		return (check_string_keys(key));
	return (0);
}
