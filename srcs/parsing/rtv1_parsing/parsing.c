/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:25:28 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/04 19:56:16 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_scene			*rtv1_parsing(t_elem *begin)
{
	t_scene		*scene;
	t_scene		*prev_scene;
	t_elem		*curr;
	int			nbr_scene;
	t_scene		*first_scene;

	scene = NULL;
	prev_scene = NULL;
	nbr_scene = 0;
	check_type_of_key("parent_element", begin->type);
	curr = begin->value.arrayi;
	if (curr == NULL && SCENE_REQUIRED)
		ft_error(SCENE_IS_REQUIRED);
	while (curr)
	{
		scene = parse_scene(curr);
		if (prev_scene == NULL)
			first_scene = scene;
		else
			prev_scene->next = scene;
		prev_scene = scene;
		curr = curr->next;
	}
	free_elem(begin);
	return (first_scene);
}
