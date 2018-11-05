/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:11:39 by cvermand          #+#    #+#             */
/*   Updated: 2018/05/10 21:18:30 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtvone.h>

t_v3	ft_v3_sustract(const t_v3 *a, const t_v3 *b)
{
	return ((t_v3){.x = a->x - b->x, 
			.y = a->y - b->y, 
			.z = a->z - b->z
			});
}

t_v3	ft_v3_add(const t_v3 *a, const t_v3 *b)
{
	return ((t_v3){.x = a->x + b->x, 
			.y =a->y + b->y, 
			.z = a->z + b->z
			});
}

t_v3	ft_v3_div(const t_v3 *a, const t_v3 *b)
{
	return ((t_v3){.x = a->x / b->x, 
			.y = a->y / b->y, 
			.z = a->z / b->z
			});
}

t_v3	ft_v3_multi(const t_v3 *a, const t_v3 *b)
{
	return ((t_v3){
			.x = a->x * b->x, 
			.y = a->y * b->y, 
			.z = a->z * b->z
			});
}

t_v3	ft_v3_scalar(const t_v3 *a, double s)
{
	return ((t_v3){
			.x = a->x * s, 
			.y = a->y * s, 
			.z = a->z * s
			});
}

double	ft_v3_dot(const t_v3 *a, const t_v3 *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}
