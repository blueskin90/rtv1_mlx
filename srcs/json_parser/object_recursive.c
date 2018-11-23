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
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	while ((*line)[*i] == ',')
	{
		*i = *i + 1;
		current->next = json_recursive(fd, line, i);
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			return (current);
	}
	if ((*line)[*i] != '}')
	{
		printf("ICI ?\n");
		ft_error(NO_CLOSING_BRACKETS);
	}
	current->closed = 1;
	return (current);
}

