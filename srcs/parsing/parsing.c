/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:25:28 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 18:37:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	rtv1_parsing(t_elem *begin)
{
		t_scene		*scene;
		t_env		*env;
		t_scene		*prev_scene;
		t_elem		*curr;
		int			nbr_scene;


		env = env_get();
		scene = NULL;
		prev_scene = NULL;
		nbr_scene = 0;
		if (!check_type_of_key("parent_element", begin->type))
				ft_error(FIRST_ELEM_BAD_FORMAT);
		curr = begin->value.arrayi;
		if (curr == NULL && SCENE_REQUIRED)
				ft_error(SCENE_IS_REQUIRED);
		while (curr)
		{
				scene = parse_scene(curr);
				if (prev_scene == NULL)
						env->scene = scene;
				else
						prev_scene->next = scene;
				prev_scene = scene;
				curr = curr->next;
		}
		// Est-ce qu'on peut donner un fichier json vide et esperer une  valeur par defayt ? 
		//
}
