/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:07:17 by toliver           #+#    #+#             */
/*   Updated: 2018/12/24 03:55:41 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				print_scenes(t_scene *scene)
{
	if (scene == NULL)
	{
		printf("	No scene at the moment\n");
		return ;
	}
	printf("	== /!\\ PRINTING SCENES /!\\ ==\n");
	while (scene)
	{
		printf("		name : %s\n", scene->name);
	//	print_objects(scene->objs);
	//	print_lights(scene->lights);
	//	print_cameras(scene->cameras);
		scene = scene->next;
	}
}
