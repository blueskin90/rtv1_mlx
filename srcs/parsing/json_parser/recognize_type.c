/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:59:29 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:36:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int			recognize_type(t_elem *current, char **line, int *i)
{
	int	type_found;

	if ((type_found = json_recognize_number(current, *line, i)) != 0)
	{
		if (DEBUG_PRINT)
			printf("position of string : %s\n", &(*line)[*i]);
		return (type_found);
	}
	else if ((type_found = json_recognize_string(current, *line, i)) != 0)
		return (type_found);
	else if ((type_found = json_recognize_bool(current, *line, i)) != 0)
		return (type_found);
	else if ((type_found = json_recognize_null(current, *line, i)) != 0)
		return (type_found);
	else 
		json_error(VALUE_NOT_RECOGNIZED);
	return (0);
}
