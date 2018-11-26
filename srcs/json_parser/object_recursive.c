/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_recursive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:57:42 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 02:58:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

t_elem		*json_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	type_found = 0;
	printf("NEW OBJECT ELEMENT\n");
	current = create_elem();
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	if ((recognize_key(i, current, *line, fd)) == 0)
		error_free_line(*line, KEY_NOT_FOUND);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	if ((type_found = json_recognize_array(current, line, i, fd)) != 0)
		type_found = current->type; // INUTILE;
	else if ((type_found = json_recognize_object(current, line, i, fd)) != 0)
		type_found = current->type; // INUTILE;
	else if (!(recognize_type(current, line, i)))
		ft_error(VALUE_NOT_RECOGNIZED);
		printf("key : %s\n", current->key);
	printf("TYPE RECOGNIZED s : %s, whole line: %s\n", &(*line)[*i], *line);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	printf("after cleaning : %s whole line : %s\n", &(*line)[*i], *line);
	/*if ((*line)[*i] != '}' && current->type == OBJECT)
	{
		printf("ICI ?\n");
		ft_error(NO_CLOSING_BRACKETS);
	} else if ((*line)[*i] == '}' && current->type != OBJECT)
		return (current);
	else if ((*line)[*i] == '}')
	{
		printf("end of object found : %s, key : %s\n",  &(*line)[*i], current->key);
		*i = *i + 1;
		current->closed = 1;
	}*/
	while ((*line)[*i] == ',')
	{
		printf("SIBLING\n");
		*i = *i + 1;
		current->next = json_recursive(fd, line, i);
		printf("back from sibling\n");
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			return (current);
	}
	printf("after siblings : %s whole line : %s\n", &(*line)[*i], *line);
	return (current);
}

