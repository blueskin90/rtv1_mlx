/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:59:04 by cvermand          #+#    #+#             */
/*   Updated: 2018/05/11 16:30:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

int		in_sphere(t_v3 *vec_r, const t_v3 *vec_o, t_obj *circle)
{
	double	disc;
	double	b;
	double	c;
	double	t[2];
	t_v3	vec_c;

	vec_c = ft_v3_sustract(&circle->pt, vec_o);
	b = ft_v3_dot(vec_r, &vec_c);
	if (b < 0)
		return (0);
	c = ft_v3_dot(&vec_c, &vec_c) - (b * b);
	if (c > circle->scale * circle->scale)
		return (0);
	disc = sqrt((circle->scale * circle->scale) - c);
	if (disc >= 0)
	{
		t[0] = (b - disc);
		t[1] = (b + disc);
		if (t[0] > 0 && (t[1] > t[0] || t[1] < 0))
			return (t[0]);
		else if (t[1] > 0)
			return (t[1]);
	}
	return (0);
}
