/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:53:30 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 01:07:07 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

int			json_recognize_string(t_elem *current, char *line, int *i)
{
	int		len;
	char	*str;
	int		begin;
	
	printf("ENTERING STRING PARSER i : %d\n", *i);
	len = 0;
	if (line[*i] != '"')
	{
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
		ft_error(JSON_PARSING_ERROR);
	*i = *i + 1;
	if ((str = ft_strsub(line, begin, (size_t)len)) == NULL)
		ft_error(MALLOC_FAIL);
	printf("string : %s\n", str);
	current->type = STRING;
	current->value.stringy = str;
	return (1);
}
