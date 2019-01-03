/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 22:12:28 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*t_color		init_color(float r, float g, float b, int value)
{
//	return (t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
}*/

t_rgb		parse_color(t_elem *elem, int required)
{
	t_elem		*child_elem;
	t_rgb		color;

	color = (t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		color.value = parse_hex(find_elem_by_key(child_elem, "hex"));
		color = parse_rgb(child_elem, color);
		if (ft_min(color.r, color.g, color.b) != INFINITY
				&& color.value != -1)
		{
			color = default_rgb(color,
					(t_rgb){.r = 0, .g = 0, .b = 0, .value = 0});
			if (color.value != rgb_getvalue(color))
				ft_error(RGB_HEX_CONFLICT);
		}
		else if (color.value != -1)
		{
			color.r = color.value >> 16;
			color.g = (color.value >> 8) & 0xFF;
			color.b = (color.value) & 0xFF;
		}
		else if (ft_min(color.r, color.g, color.b) != INFINITY)
		{
			color = default_rgb(color,
					(t_rgb){.r = 0, .g = 0, .b = 0, .value = 0});
			rgb_updatevalue(&color);
		}
		else
		{
			color = default_rgb(color,
			(t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff});
		}
	}
	else if (required)
		is_required(elem->key, 0);
	else
		color = (t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
	color.r = color.r / 255.0;
	color.g = color.g / 255.0;
	color.b = color.b / 255.0;
	return (color);
}
