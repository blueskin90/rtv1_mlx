/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:28:41 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/04 18:22:18 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	show_one_key(t_key *elem, int padding)
{
	t_key	*bro;
	t_key	*child;

	printf("%*c--------\n", padding, '-');
	printf("%*cname : %s\n", padding,' ', elem->name);
	printf("%*crequired : %d\n", padding,' ', elem->required);
	if (elem->type == INTEGER)
	{
		printf("%*ctype : %s\n",padding,' ', "INTEGER");
		printf("%*cvalue : %d\n", padding, ' ', elem->defaulty.inty);
	}
	if (elem->type == FLOAT)
	{
		printf("%*ctype : %s\n",padding,' ', "FLOAT");
		printf("%*cvalue : %f\n", padding,' ', elem->defaulty.floaty);
	}
	if (elem->type == STRING)
	{
		printf("%*ctype : %s\n",padding,' ', "STRING");
		printf("%*cvalue : %s\n", padding,' ', elem->defaulty.stringy);
	}
	if (elem->type == BOOL)
	{
		printf("%*ctype : %s\n",padding,' ', "BOOL");
		printf("%*cvalue : %d\n", padding,' ', elem->defaulty.booly);
	}
	if (elem->type == NULL_ELEM)
	{
		printf("%*ctype : %s\n",padding,' ', "NULL");
		printf("%*cvalue : %d\n", padding,' ', elem->defaulty.nully);
	}
	if (elem->defaulty.inty != 0)
	{
		printf("%*cdefault : \n",padding,' ');
		show_one_elem((t_elem *)elem->defaulty.objecty, padding + 10);
	}
	if (elem->type == ARRAY)
	{
		printf("%*ctype : %s\n",padding,' ', "ARRAY");
		bro = elem->next;
		while (bro)
		{
			show_one_key(bro, padding + 10);
			bro = bro->next;
		}
	}
	if (elem->type == OBJECT)
	{
		printf("%*ctype : %s\n",padding,' ', "OBJECT");
		bro = elem->next;
		child = elem->child;
		if (child)
			show_one_key(child, padding + 10);
		while (bro)
		{
			show_one_key(bro, padding);
			bro = bro->next;
		}
	}
	printf("%*c--------\n", padding, '-');
}

void		print_keys(t_key *key, int padding)
{
	t_key	*current;

	current = key;
	show_one_key(current, padding);
	/*while (current)
	{
		current = current->next;
	}*/

}
