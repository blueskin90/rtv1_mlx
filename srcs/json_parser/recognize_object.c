/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:00:09 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 03:17:28 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int			json_recognize_object(t_elem *current, char **line, int *i, int fd)
{
	t_elem	*child;
	t_elem	*previous;
	char	first_elem;

	first_elem = 1;
	child = NULL;
	previous = NULL;
	printf("ENTERING OBJECT PARSER i : %d\n", *i);
	if ((*line)[*i] != '{')
	{
		printf("value is not an object\n");
		return (0);
	}
	*i = *i + 1;
	current->type = OBJECT;
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
	printf("pos of string : %s\n", &(*line)[*i]);
	while ((*line)[*i] == ',' || (first_elem && ((*line)[*i] != '}')))
	{
		first_elem = 0;
		if ((*line)[*i] == ',') 
			*i = *i + 1;
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
		printf("Child element : \n");
		child = json_recursive(fd, line, i);
		printf("Back from child element\n");
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			ft_error(UNEXPECTED_END_OF_FILE);
		if (!current->value.objecty)
			current->value.arrayi = (void *)child;
		if (previous)
			previous->next = child;
		previous = child;
	}
	if ((*line)[*i] != '}')
		ft_error(OBJECT_BAD_FORMAT);
	current->closed = 1;
	*i = *i + 1;
	return (current->type);
}
