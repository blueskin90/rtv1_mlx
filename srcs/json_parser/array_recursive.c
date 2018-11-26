/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_recursive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:57:11 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/23 02:57:27 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

t_elem		*array_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	printf("NEW ARRAY ELEMENT\n");
	type_found = 0;
	current = create_elem();
	if ((type_found = json_recognize_array(current, line, i, fd)) == 1)
		type_found = current->type; // INUTILE;
	else if ((type_found = json_recognize_object(current, line, i, fd)) != 0)
		type_found = current->type; // INUTILE;
	else if (!(recognize_type(current, line, i)))
		ft_error(VALUE_NOT_RECOGNIZED);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	if (!((*line)[*i] != ',' || (*line)[*i] != ']'))
		ft_error(NO_CLOSING_BRACKETS);
	return (current);
}
