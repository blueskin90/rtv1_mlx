/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_projection_struct.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:37:35 by cvermand          #+#    #+#             */
/*   Updated: 2018/04/18 16:17:54 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmatrice.h"

t_proj		*create_projection_struct(double fov, double ratio, double near, double far)
{
	t_proj	*new;

	if (!(new = ft_memalloc(sizeof(t_proj))))
		return (NULL);
	new->fov = fov;
	new->ratio = ratio;
	new->near = near;
	new->far = far;
	return (new);
}
