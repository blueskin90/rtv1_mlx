/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magnitude_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:15:49 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/21 22:37:46 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

double		magnitude_vector(t_vector *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}
