/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 00:54:47 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:35:37 by cvermand         ###   ########.fr       */
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
	if (DEBUG_PRINT)
		printf("ENTERING ARRAY PARSER i : %d\n", *i);
	if ((*line)[*i] != '[')
	{
		if (DEBUG_PRINT)
			printf("value is not an array\n");
		return (0);
	}
	*i = *i + 1;
	current->type = ARRAY;
	current->value.arrayi = NULL;
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
			json_error(UNEXPECTED_END_OF_FILE);
	while ((*line)[*i] == ',' || (first_elem && (*line)[*i] != ']'))
	{
		if ((*line)[*i] == ',') 
			*i = *i + 1;
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			json_error(UNEXPECTED_END_OF_FILE);
		child = array_recursive(fd, line, i);
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			json_error(UNEXPECTED_END_OF_FILE);
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
	if (DEBUG_PRINT)
		printf("ARRAY  OUT  : %s i : %d\n", &((*line)[*i]), *i);
	if ((*line)[*i] != ']')
		json_error(ARRAY_BAD_FORMAT);
	current->closed = 1;
	*i = *i + 1;
	return (current->type);
}
