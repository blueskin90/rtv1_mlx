/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 00:54:47 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 15:26:10 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int			json_recognize_array(t_elem *current, char **line, int *i, int fd)
{
	t_elem	*child;
	t_elem	*previous;
	char	first_elem;

	first_elem = 1;
	child = NULL;
	previous = NULL;
	if ((*line)[*i] != '[')
		return (0);
	*i = *i + 1;
	current->type = ARRAY;
	current->value.arrayi = NULL;
	ignore_tab_and_spaces(line, i, fd, 0);
	while ((*line)[*i] == ',' || (first_elem && (*line)[*i] != ']'))
	{
		if ((*line)[*i] == ',')
			*i = *i + 1;
		ignore_tab_and_spaces(line, i, fd, 0);
		child = array_recursive(fd, line, i);
		ignore_tab_and_spaces(line, i, fd, 0);
		if (!current->value.arrayi)
			current->value.arrayi = (void *)child;
		if (previous)
		{
			if (previous->type != child->type)
				json_error(ARRAY_MULTIPLE_TYPE);
			previous->next = child;
		}
		previous = child;
	}
	if ((*line)[*i] != ']')
		json_error(ARRAY_BAD_FORMAT);
	current->closed = 1;
	*i = *i + 1;
	return (current->type);
}
