/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:22:40 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 01:14:19 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

/*
** AUCUNE DE CES FONCTIONS NE UPDATE LA VALUE, go faire rgb_updatevalue(&rgb)
** apres
*/

t_rgb			rgb_add(t_rgb a, t_rgb b)
{
	t_rgb		c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}

t_rgb			rgb_mul_rgb(t_rgb a, t_rgb b)
{
	t_rgb		c;

	c.r = a.r * b.r;
	c.g = a.g * b.g;
	c.b = a.b * b.b;
	return (c);
}

t_rgb			rgb_mul(t_rgb a, float scalar)
{
	t_rgb		b;

	b.r = a.r * scalar;
	b.g = a.g * scalar;
	b.b = a.b * scalar;
	return (b);
}

t_rgb			rgb_div(t_rgb a, float scalar)
{
	t_rgb		b;

	b.r = a.r / scalar;
	b.g = a.g / scalar;
	b.b = a.b / scalar;
	return (b);
}
