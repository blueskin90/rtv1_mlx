/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:59:33 by toliver           #+#    #+#             */
/*   Updated: 2019/01/07 16:31:41 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_scene		*json_parsing(char **files, t_args *args)
{
	t_elem			*json;
	t_scene			*scene;

	if (files && *files)
	{
		json = json_parser(*files);
		if (args->debug_mode)
			show_every_elem(json, 0);
		scene = rtv1_parsing(json);
		return (scene);
	}
	return (NULL);
}

t_scene				*parsing(t_args *args)
{
	t_scene		*scene;

	scene = json_parsing(args->files, args);
	if (args->verbose_mode == PARSING || args->verbose_mode == ALL_VERBOSE)
		verbose_parsing(scene);
	return (scene);
}
