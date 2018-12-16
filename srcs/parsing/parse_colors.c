/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 15:02:20 by cvermand         ###   ########.fr       */
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
	else if ( len > 1 && str[0] == '0' && str[1] == 'x')
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

int			parse_hex(t_elem *elem)
{
	int		hex;

	hex = -1;
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		hex = hex_color_to_int(elem);
		return hex;
	}
	return (hex);
}

t_RGB		parse_rgb(t_elem *elem, t_RGB color)
{
	float	r;
	float	g;
	float	b;

	r = parse_float(find_elem_by_key(elem, "r"));
	g = parse_float(find_elem_by_key(elem, "g"));
	b = parse_float(find_elem_by_key(elem, "b"));
	if (ft_min(r, g, b) == INFINITY && COLOR_RGB_REQUIRED)
		is_required("RGB of color", false);
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

t_RGB		parse_color(t_elem *elem)
{
	t_elem		*child_elem;
	t_RGB		color;

	if (elem != NULL)
	{
		printf("parse color %s\n", elem->key);
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		color.value = parse_hex(find_elem_by_key(child_elem, "hex"));
		color = parse_rgb(child_elem, color);
		printf("RGB : [%f, %f, %f]\n", color.r, color.g, color.b);
		printf("HEX : %#X\n", color.value);
		if (ft_min(color.r, color.g, color.b) != INFINITY 
				&& color.value != -1)
		{
			color = default_rgb(color, 
					(t_RGB){.r = 0, .g = 0, .b = 0, .value = 0});
			if ( color.value != get_rgb((unsigned char) color.r, (unsigned char) color.g, (unsigned char) color.b))
				ft_error(RGB_HEX_CONFLICT);
		}
		else if (color.value != -1)
		{
			printf("HEX ONLY\n");
			color.r = color.value >> 16;
			color.g = (color.value >> 8) & 0xFF;
			color.b = (color.value) & 0xFF;
			printf("RGB : [%f, %f, %f]\n", color.r, color.g, color.b);
			printf("HEX : %X\n", color.value);
		}
		else if (ft_min(color.r, color.g, color.b) != INFINITY)
		{
			color = default_rgb(color, 
					(t_RGB){.r = 0, .g = 0, .b = 0, .value = 0});
			color.value = get_rgb((unsigned char) color.r, (unsigned char) color.g, (unsigned char) color.b);
		}
		else 
		{
			printf("FIRST DEFAULT VALUE\n");
			color = default_rgb(color, 
					(t_RGB){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff});	
		}
		return (color);
	}
	else if (COLOR_REQUIRED)
		is_required("colors", false);
	else 
	{
		printf("second DEFAULT VALUE\n");
		color = (t_RGB){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
	}
	return (color);
}
