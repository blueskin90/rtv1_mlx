/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_singleton.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:26:21 by toliver           #+#    #+#             */
/*   Updated: 2018/12/11 16:26:38 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_win				*win_get(void)
{
	return(env_get()->win);
}

int					win_getx(void)
{
	return(env_get()->win->winx);
}

int					win_gety(void)
{
	return(env_get()->win->winy);
}
