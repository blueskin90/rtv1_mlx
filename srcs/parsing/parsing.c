/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 03:59:33 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 06:01:29 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*parsing(t_args *args)
{
	t_scene		*scene;

	step_set(PARSING);
	if (args->parse_mode == STANDARD)
		scene = tmp_parsing();
	else
		scene = json_parsing(args->files);
	verbose_parsing(scene);
	return (scene);
}
