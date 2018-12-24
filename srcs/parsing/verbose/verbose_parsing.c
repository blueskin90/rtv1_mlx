/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 04:03:42 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 06:01:28 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			verbose_parsing(t_scene *scene)
{
	ft_printf("\n/!\\ == Verbose for parsing == /!\\\n\n");
	print_scenes(scene);
	ft_printf("==== end of parsing verbose ====\n\n");
}
