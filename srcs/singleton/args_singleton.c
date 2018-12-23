/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_singleton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 16:50:14 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 02:36:25 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_args	**args_getptr(void)
{
	static t_args	*ptr = NULL;

	return (&ptr);
}

t_args			*args_get(void)
{
	return(*(args_getptr()));
}

void			args_set(t_args *args)
{
	t_args		**ptr;
	
	ptr = args_getptr();
	if (ptr == NULL)
		printf("args_set has an args_getptr == null\n");
	*ptr = args;
}

int				verbose_mode_get()
{
	return ((int)(args_get()->verbose_mode));
}

int				render_mode_get()
{
	return ((int)(args_get()->render_mode));
}

int				renderer_mode_get()
{
	return ((int)(args_get()->renderer_mode));
}

int				parse_mode_get()
{
	return ((int)(args_get()->parse_mode));
}

int				debug_mode_get()
{
	return ((int)(args_get()->debug_mode));
}

char			**files_get()
{
	return (args_get()->files);
}
