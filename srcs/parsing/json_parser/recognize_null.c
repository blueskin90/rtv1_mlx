/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_null.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:56:22 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 17:51:43 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int		json_recognize_null(t_elem *current, char *line, int *i)
{
	if (DEBUG_PRINT)
		printf("ENTERRING NULL PARSER \n");
	if (ft_strncmp(&line[*i], "null", 4) == 0)
	{
		*i = *i + 4;
		current->type = NULL_ELEM;
		current->value.nully = 0;
		return (1);
	}
	return (0);
}
