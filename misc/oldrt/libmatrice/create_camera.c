/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 18:25:47 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/03 18:27:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libmatrice.h"

t_proj		*create_camera()
{
	t_proj	*new;

	if (!(new = ft_memalloc(sizeof(t_proj))))
		return (NULL);
	new->fov = NULL;
	new->ratio = NULL;
	new->near = NULL;
	new->far = NULL;
	return (new);
}
