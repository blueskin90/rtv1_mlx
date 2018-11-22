/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem_architecture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 00:36:25 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 01:07:51 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void	show_elem(t_elem *elem)
{
	if (elem)
	{
		printf("main : %d,\nclosed : %d,\nkey : %s\n",
				elem->main, elem->closed, elem->key); 
		printf("ELEM TYPE : %d\n", elem->type);
		if (elem->type == INTEGER)
		{
		}
	}
}
static void	show_one_elem(t_elem *elem, int padding)
{

	printf("%*c--------\n", padding, '-');
	printf("key : %*s\n", padding, elem->key);
	printf("closed : %*d\n", padding, elem->closed);
	printf("type : %*d\n",padding,  elem->type);
	if (elem->type == INTEGER)
		printf("value : %*d\n", padding, elem->value.inty);
	if (elem->type == STRING)
		printf("value : %*s\n", padding, elem->value.stringy);
	printf("%*c--------\n", padding, '-');
}

void	show_every_elem(t_elem *elem, int padding)
{
	t_elem *current;

	current = elem;
	while (current)
	{
		show_one_elem(current, padding);
		current = current->next;
	}
}
