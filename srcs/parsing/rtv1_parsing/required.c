/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   required.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:35:23 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 19:40:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
// TODO verifier que je n'utilise pas elem->key quand je fais appel a cette fonction
float		required_float(float number, int required, char *error)
{
	if (number == INFINITY && required)
		is_required(error, 0);
	return (number);
}

t_vec		required_vec(t_vec vec, int required, char *error)
{
	if (min_of_vec(vec) == INFINITY && required)
		is_required(error, 0);
	return (vec);
}
