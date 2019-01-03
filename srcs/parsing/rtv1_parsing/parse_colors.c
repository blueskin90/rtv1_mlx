/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 20:51:44 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 22:27:37 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_rgb		init_color(float r, float g, float b, int value)
{
	return ((t_rgb){.r = r, .g = g, .b = b, .value = value});
}

static t_rgb		color_from_value(int value)
{
	t_rgb	color;

	color.r = value >> 16;
	color.g = (value >> 8) & 0xFF;
	color.b = (value) & 0xFF;
	color.value = value;
	return (color);
}

static t_rgb		color_from_rgb_and_value(t_rgb color)
{
	t_rgb	new;

	new = default_rgb(color,
			(t_rgb){.r = 0, .g = 0, .b = 0, .value = 0});
	if (new.value != rgb_getvalue(new))
		ft_error(RGB_HEX_CONFLICT);
	return (new);
}

static t_rgb		color_from_rgb(t_rgb color)
{
	color = default_rgb(color,
			(t_rgb){.r = 0, .g = 0, .b = 0, .value = 0});
	rgb_updatevalue(&color);
	return (color);
}

t_rgb				parse_color(t_elem *elem, int required)
{
	t_elem		*child_elem;
	t_rgb		c;

	c = (t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
	if (elem != NULL)
	{
		check_type_of_key(elem->key, elem->type);
		child_elem = elem->value.objecty;
		c = parse_rgb_and_val(child_elem);
		if (ft_min(c.r, c.g, c.b) != INFINITY && c.value != -1)
			c = color_from_rgb_and_value(c);
		else if (c.value != -1)
			c = color_from_value(c.value);
		else if (ft_min(c.r, c.g, c.b) != INFINITY)
			c = color_from_rgb(c);
		else
			c = default_rgb(c,
				(t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff});
	}
	else if (required)
		is_required(elem->key, 0);
	else
		c = (t_rgb){.r = 255.0, .g = 255.0, .b = 255.0, .value = 0xffffff};
	c = init_color(c.r / 255.0, c.g / 255.0, c.b / 255.0, c.value);
	return (c);
}
