/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:53:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:36:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int			json_recognize_string(t_elem *current, char *line, int *i)
{
	int		len;
	char	*str;
	int		begin;
	
	if (DEBUG_PRINT)
		printf("ENTERING STRING PARSER i : %d\n", *i);
	len = 0;
	if (line[*i] != '"')
	{
		if (DEBUG_PRINT)
			printf("value is not a string\n");
		return (0);
	}
	*i = *i + 1;
	begin = *i;
	while (line[*i] != '\0' && line[*i] != '"')
	{
			len++;
			*i = *i + 1;
	}
	if (line[*i] != '"')
		json_error(JSON_PARSING_ERROR);
	*i = *i + 1;
	if ((str = ft_strsub(line, begin, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	if (DEBUG_PRINT)
		printf("string : %s\n", str);
	current->type = STRING;
	current->value.stringy = str;
	return (1);
}
