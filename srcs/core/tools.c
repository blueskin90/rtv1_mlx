/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:16:49 by toliver           #+#    #+#             */
/*   Updated: 2018/12/10 17:15:45 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float				maxf(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float				minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int					clampi(int a, int inf_limit, int sup_limit)
{
	if (a < inf_limit)
		return (inf_limit);
	if (a > sup_limit)
		return (sup_limit);
	return (a);	
}

float					clampf(float a, float inf_limit, float sup_limit)
{
	if (a < inf_limit)
		return (inf_limit);
	if (a > sup_limit)
		return (sup_limit);
	return (a);	
}

