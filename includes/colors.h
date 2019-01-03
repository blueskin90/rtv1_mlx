/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:17:11 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 19:02:44 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#include <math.h>

typedef struct		s_rgb
{
	float			r;
	float			g;
	float			b;
	int				value;
}					t_rgb;

/*
** INIT FUNCTIONS
*/

t_rgb				rgb_init(int value);
void				rgb_updatevalue(t_rgb *rgb);
int					rgb_getvalue(t_rgb rgb);

/*
** RGB FUNCTIONS
*/

t_rgb				rgb_clamp(t_rgb a);
t_rgb				rgb_mul_rgb(t_rgb a, t_rgb b);
t_rgb				rgb_mul(t_rgb a, float scalar);
t_rgb				rgb_div(t_rgb a, float scalar);
t_rgb				rgb_add(t_rgb a, t_rgb b);

#endif
