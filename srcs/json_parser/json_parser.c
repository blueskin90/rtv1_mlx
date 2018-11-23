/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 03:26:33 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int		key_cmp(t_elem *elem)
{
	t_elem	*next;
	while (elem && elem->next)
	{
		next = elem->next;
		while (next)
		{
			if (ft_strcmp(elem->key, next->key) == 0)
				return (1);
			next = next->next;
		}
		elem = elem->next;
	}
	return (0);
}

int		check_for_same_key_in_object(t_elem *begin)
{
	t_elem	*current;
	t_elem	*child;
	
	child = NULL;
	current = begin;
	while (current)
	{
		if (current->type == OBJECT)
		{
			if (key_cmp(current))
				return (1);
			child = (t_elem *)current->value.objecty;
			check_for_same_key_in_object(child);
		}
		if (current->type == ARRAY)
		{
			child = (t_elem *)current->value.arrayi;
			check_for_same_key_in_object(child);
		}
		current = current->next;
	}
	return (0);
}

t_elem	*json_parser(char *file)
{
	int		fd;
	char	*line;
	int		ret;
	t_elem	*begin;
	int		x;

	begin = create_elem();
	line = NULL;
	x = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(FD_FAIL);	
	if ((ret = ft_get_next_line(fd, &line)) != 1)
		ft_error(EMPTY_FILE);
	printf("size elem : %lu\n", sizeof(t_elem));
	printf("%s\n", line);
	if (line[0] == '{')
	{
		begin->type = OBJECT;
		begin->value.objecty = json_recursive(fd, &line, &x);
	}
	else if (line[0] == '[')
	{
		begin->type = ARRAY;
		begin->value.arrayi = array_recursive(fd, &line, &x);
	}
	else {
		ft_error(BAD_BEGIN_OF_FILE);
	}
	if (check_for_same_key_in_object(begin))
		ft_error(SAME_KEY_NAME);
	// look for similar KEYS => error
	// verify that file is done
	show_every_elem(begin, 0);
}
