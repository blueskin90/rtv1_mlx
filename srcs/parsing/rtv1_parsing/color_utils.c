/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:04:43 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 22:05:56 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*string_to_lower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

int			parse_hex(t_elem *elem)
{
	int		hex;

	hex = -1;
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		hex = hex_color_to_int(elem);
		return (hex);
	}
	return (hex);
}

t_rgb		parse_rgb(t_elem *elem, t_rgb color)
{
	float	r;
	float	g;
	float	b;

	r = parse_float(find_elem_by_key(elem, "r"));
	g = parse_float(find_elem_by_key(elem, "g"));
	b = parse_float(find_elem_by_key(elem, "b"));
	if (ft_min(r, g, b) == INFINITY && COLOR_RGB_REQUIRED)
		is_required("RGB of color", 0);
	if (r != INFINITY && !(r <= 255 && r >= 0))
		ft_error(RGB_BAD_VAL);
	if (g != INFINITY && !(g <= 255 && g >= 0))
		ft_error(RGB_BAD_VAL);
	if (b != INFINITY && !(b <= 255 && b >= 0))
		ft_error(RGB_BAD_VAL);
	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

int			hex_color_to_int(t_elem *elem)
{
	int		value;
	char	*str;
	char	*compare_str;
	int		len;

	check_type_of_key(elem->key, elem->type);
	str = string_to_lower(elem->value.stringy);
	len = ft_strlen(str);
	value = -1;
	if (len > 0 && str[0] == '#')
	{
		str = &str[1];
		value = ft_atoi_base(str, 16);
	}
	else if (len > 1 && str[0] == '0' && str[1] == 'x')
	{
		str = &str[2];
		value = ft_atoi_base(str, 16);
	}
	else if (len > 0 && (ft_isdigit(str[0]) ||
			(str[0] >= 'a' && str[0] <= 'f')))
		value = ft_atoi_base(str, 16);
	else
		ft_error(BAD_FORMAT_HEX);
	compare_str = ft_itoa_hex(value, 0);
	if (ft_strcmp_case_insensitive(compare_str, str) != 0)
		ft_error(BAD_FORMAT_HEX);
	free(compare_str);
	if (value > 0xFFFFFF || value < 0)
		ft_error(HEX_NOT_IN_LIMIT);
	return (value);
}
