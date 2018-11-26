/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 00:54:47 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 02:31:10 by cvermand         ###   ########.fr       */
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
	printf("ENTERING ARRAY PARSER i : %d\n", *i);
	if ((*line)[*i] != '[')
	{
		printf("value is not an array\n");
		return (0);
	}
	*i = *i + 1;
	current->type = ARRAY;
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
	while ((*line)[*i] == ',' || (first_elem && (*line)[*i] != ']'))
	{
		if ((*line)[*i] == ',') 
			*i = *i + 1;
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
		child = array_recursive(fd, line, i);
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
		if (!current->value.arrayi)
			current->value.arrayi = (void *)child;
		if (previous)
		{
			if (previous->type != child->type)
				ft_error(ARRAY_MULTIPLE_TYPE);
			previous->next = child;
		}
		previous = child;
	}
	printf("ARRAY  OUT  : %s i : %d\n", &((*line)[*i]), *i);
	if ((*line)[*i] != ']')
		ft_error(ARRAY_BAD_FORMAT);
	current->closed = 1;
	*i = *i + 1;
	return (current->type);
}
