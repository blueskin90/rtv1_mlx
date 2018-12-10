/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/10 21:16:19 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		*new_color()
{
	t_color	*color;

	color = (t_color*)ft_malloc(sizeof(t_color));
	ft_bzero(color);
	return (color);
}

int			hex_color_to_int(t_elem *elem)
{
	int		value;
	char	*str;
	char	*compare_str;

	check_type_of_key(elem->key, elem->type);
	str = elem->value.stringy;
	if (str[0] == '#')
	{
		str = &str[1];
		value = ft_atoi_base(str, 16);
	}
	else if (str[0] == '0' && ft_tolower(str[1]) == 'x')
	{
		str = &str[2];
		value = ft_atoi_base(str, 16);
	}
	else if (ft_isdigit(str[0]) || (ft_tolower(str[0]) >= 'a' && 
			ft_tolower(str[0] <= 'f')))
		value = ft_atoi_base(str, 16);
	else 
		ft_error(BAD_FORMAT_HEX);
	compare_str = ft_itoa_base(value);

}

t_color		*parse_colors(t_elem	*elem)
{
	t_elem		*child_elem;
	t_color		*color;
	
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		color = new_color();
		if ((child_elem = find_elem_by_key("")) != NULL)
			color->value = 
			
	}
	else if (COLOR_REQUIRED)
		is_required("colors", false);
	else {
		color = new_color();
		color->r = INFINITY;
		color->g = INFINITY;
		color->b = INFINITY;
		color->value = -1;
		return (color);
	}

}
