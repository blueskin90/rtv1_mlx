/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:21:07 by toliver           #+#    #+#             */
/*   Updated: 2019/01/04 21:42:52 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene				*json_parsing(char **files)
{
	t_elem			*json;
	t_scene			*scene;

	json = json_parser(*files);
	scene = rtv1_parsing(json);
	return (scene);
}
/*
** PENSER A FAIRE UNE LOOP QUI ALLOC TOUTES LES SCENES SI BESOIN
*/
