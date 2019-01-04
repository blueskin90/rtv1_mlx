/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:59:33 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 17:52:31 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*parsing(t_args *args)
{
	t_scene		*scene;

	scene = json_parsing(args->files);
	if (args->verbose_mode == PARSING || args->verbose_mode == ALL_VERBOSE)
		verbose_parsing(scene);
	return (scene);
}
