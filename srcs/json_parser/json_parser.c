/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/05 17:54:37 by cvermand         ###   ########.fr       */
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
								ft_error(SAME_KEY_NAME);
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
						if (current->value.objecty)
						{
								child = (t_elem *)current->value.objecty;
								key_cmp(child);
								check_for_same_key_in_object(child);
						}
				}
				if (current->type == ARRAY)
				{
						if (current->value.arrayi)
						{
								child = (t_elem *)current->value.arrayi;
								check_for_same_key_in_object(child);
						}
				}
				current = current->next;
		}
		return (0);
}
void	check_end_of_json_file(char *line, int fd)
{
		int ret ;
		if ((ret = ft_get_next_line(fd, &line)) != 0)
				ft_error(END_OF_FILE_BAD_FORMAT);
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
		x = 0;
		if ((fd = open(file, O_RDONLY)) == -1)
				ft_error(FD_FAIL);	
		if ((ret = ft_get_next_line(fd, &line)) != 1)
				ft_error(EMPTY_FILE);
		if (line[0] == '{')
				json_recognize_object(begin, &line, &x, fd);
		else if (line[0] == '[')
				json_recognize_array(begin, &line, &x, fd);
		else 
				ft_error(BAD_BEGIN_OF_FILE);
		check_end_of_json_file(line, fd);
		check_for_same_key_in_object(begin);
//		show_every_elem(begin, 0);
		return (begin);
}
