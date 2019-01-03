/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:25:28 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:38:46 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void free_elem(t_elem *begin)
{
	t_elem	*bro;

	if (elem->type == STRING)
		free(elem->value.stringy);
	if (elem->type == OBJECT)
	{
		bro = (t_elem *)elem->value.objecty;
		if (bro)
		{
			free_elem(bro);
			bro = bro->next;
		}
	}
	if (elem->type == ARRAY)
	{
		bro = (t_elem *)elem->value.arrayi;
		if (bro)
		{
			show_one_elem(bro, padding + 10);
			bro = bro->next;
		}
	}

}

t_scene	*rtv1_parsing(t_elem *begin)
{
		t_scene		*scene;
		t_scene		*prev_scene;
		t_elem		*curr;
		int			nbr_scene;
		t_scene		*first_scene;

		scene = NULL;
		prev_scene = NULL;
		nbr_scene = 0;
		// TODO array pas obligatoire pour premier element
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
		// Est-ce qu'on peut donner un fichier json vide et esperer une  valeur par defayt ? 
		//
	return (first_scene);
}
