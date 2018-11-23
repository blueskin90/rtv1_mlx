/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elem_architecture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 00:36:25 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 03:17:25 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void	show_elem(t_elem *elem)
{
	if (elem)
	{
		printf("%c--------\n",  '-');
		printf("key : %s\n",  elem->key);
		printf("closed : %d\n",  elem->closed);
		printf("type : %d\n",  elem->type);
		if (elem->type == INTEGER)
			printf("value : %d\n",  elem->value.inty);
		if (elem->type == FLOAT)
			printf("value : %f\n",  elem->value.floaty);
		if (elem->type == STRING)
			printf("value : %s\n",  elem->value.stringy);
		if (elem->type == BOOL)
			printf("value : %d\n",  elem->value.booly);
		if (elem->type == NULL_ELEM)
			printf("value : %d\n",  elem->value.nully);
		printf("%c--------\n",  '-');
	}
}
static void	show_one_elem(t_elem *elem, int padding)
{
	t_elem	*bro;

	printf("%*c--------\n", padding, '-');
	printf("%*ckey : %s\n", padding,' ', elem->key);
	printf("%*cclosed : %d\n", padding,' ', elem->closed);
	if (elem->type == INTEGER)
	{
		printf("%*ctype : %s\n",padding,' ', "INTEGER");
		printf("%*cvalue : %d\n", padding, ' ', elem->value.inty);
	}
	if (elem->type == FLOAT)
	{
		printf("%*ctype : %s\n",padding,' ', "FLOAT");
		printf("%*cvalue : %f\n", padding,' ', elem->value.floaty);
	}
	if (elem->type == STRING)
	{
		printf("%*ctype : %s\n",padding,' ', "STRING");
		printf("%*cvalue : %s\n", padding,' ', elem->value.stringy);
	}
	if (elem->type == BOOL)
	{
		printf("%*ctype : %s\n",padding,' ', "BOOL");
		printf("%*cvalue : %d\n", padding,' ', elem->value.booly);
	}
	if (elem->type == NULL_ELEM)
	{
		printf("%*ctype : %s\n",padding,' ', "NULL");
		printf("%*cvalue : %d\n", padding,' ', elem->value.nully);
	}
	if (elem->type == ARRAY)
	{
		printf("%*ctype : %s\n",padding,' ', "ARRAY");
		bro = (t_elem *)elem->value.arrayi;
		while (bro)
		{
			show_one_elem(bro, padding + 10);
			bro = bro->next;
		}
	}
	if (elem->type == OBJECT)
	{
		printf("%*ctype : %s\n",padding,' ', "OBJECT");
		bro = (t_elem *)elem->value.objecty;
		while (bro)
		{
			show_one_elem(bro, padding + 10);
			bro = bro->next;
		}
	}
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
