/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_singleton.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:18:00 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:19:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_env		**env_getptr(void)
{
	static t_env	*ptr = NULL;
	return (&ptr);
}

t_env				*env_get(void)
{
	return (*(env_getptr()));
}

void				env_set(t_env *env)
{
	t_env			**ptr;

	ptr = env_getptr();
	if (ptr == NULL)
	printf("env_set has a env_getptr == null\n");
	*ptr = env;
}
