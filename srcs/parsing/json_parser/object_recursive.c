/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_recursive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:57:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:48:34 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

t_elem		*object_siblings(int fd, char **line, int *i)
{

}

t_elem		*json_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	type_found = 0;
	if (DEBUG_PRINT)
		printf("NEW OBJECT ELEMENT\n");
	current = create_elem();
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		json_error(UNEXPECTED_END_OF_FILE);
	if ((recognize_key(i, current, *line, fd)) == 0)
		error_free_line(*line, KEY_NOT_FOUND);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		json_error(UNEXPECTED_END_OF_FILE);
	if ((type_found = json_recognize_array(current, line, i, fd)) != 0)
		type_found = current->type;
	else if ((type_found = json_recognize_object(current, line, i, fd)) != 0)
		type_found = current->type;
	else if (!(recognize_type(current, line, i)))
		json_error(VALUE_NOT_RECOGNIZED);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		json_error(UNEXPECTED_END_OF_FILE);
	while ((*line)[*i] == ',')
	{
		*i = *i + 1;
		current->next = json_recursive(fd, line, i);
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			json_error(UNEXPECTED_END_OF_FILE);
	}
	return (current);
}

