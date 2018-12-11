/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/11 17:21:50 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


int			hex_color_to_int(t_elem *elem)
{
	int		value;
	char	*str;
	char	*compare_str;
	int		len;

	check_type_of_key(elem->key, elem->type);
	str = elem->value.stringy;
	len = ft_strlen(str);
	// TODO verifier HEX
	if (len > 0 && str[0] == '#')
	{
		str = &str[1];
		value = ft_atoi_base(str, 16);
	}
	else if ( len > 1 && str[0] == '0' && ft_tolower(str[1]) == 'x')
	{
		str = &str[2];
		value = ft_atoi_base(str, 16);
	}
	else if (len > 0 && ft_isdigit(str[0]) ||
			(ft_tolower(str[0]) >= 'a' && ft_tolower(str[0] <= 'f')))
		value = ft_atoi_base(str, 16);
	else 
		ft_error(BAD_FORMAT_HEX);
	compare_str = ft_itoa_base(value, 16);
	if (ft_strcmp_case_insensitive(compare_str, str) != 0)
		ft_error(BAD_FORMAT_HEX);
	free(compare_str);
	return (value);
}

int			parse_hex(t_elem *elem)
{
	int		hex;

	hex = 0;
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		hex = hex_color_to_int(elem);
		return hex;
	}
	return (INFINITY);
}

t_color		parse_rgb(t_elem *elemi, t_color *color)
{
	float	x;
	float	y;
	float	z;

	x = parse_float(find_elem_by_key(elem, "x"));
	y = parse_float(find_elem_by_key(elem, "y"));
	z = parse_float(find_elem_by_key(elem, "z"));

}

t_color		parse_color(t_elem *elem)
{
	t_elem		*child_elem;
	t_color		color;
	
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		color->value = parse_hex(find_elem_by_key(child_elem, "hex"));
			
	}
	else if (COLOR_REQUIRED)
		is_required("colors", false);
	else {
		color = new_color();
		color.r = INFINITY;
		color.g = INFINITY;
		color.b = INFINITY;
		color.value = -1;
		return (color);
	}

}
