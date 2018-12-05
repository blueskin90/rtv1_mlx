/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:25:28 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 17:52:48 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
t_elem		*find_elem_by_key(t_elem *elem, char *key)
{
	t_elem		*curr;

	curr = elem;
	printf("qweeeeeeeeeeeeeeeeeeeeeeeeeeeee\n");
	while (curr)
	{
		printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
		show_one_elem(curr, 0);
		if (curr->key != NULL && ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_env		*rtv1_parsing(t_elem *begin, t_env *env)
{
	t_scene		*scene;
	t_scene		*prev_scene;
	t_elem		*curr;
	int			nbr_scene;

	scene = NULL;
	prev_scene = NULL;
	nbr_scene = 0;	
	printf("qweqewq\n");
	curr = begin;
	if (curr->type == ARRAY && curr->value.arrayi != NULL)
	{
		curr = curr->value.arrayi;
		while (curr)
		{
			nbr_scene++;
			scene = parse_scene(curr, nbr_scene);
			if (prev_scene == NULL)
				env->scene = scene;
			else
				prev_scene->next = scene;
			prev_scene = scene;
			curr = curr->next;
		}
	}
	// Est-ce qu'on peut donner un fichier json vide et esperer une  valeur par defayt ? 
	//
	return (env);
}
