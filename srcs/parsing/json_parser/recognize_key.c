/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:34:19 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:36:36 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static char		*create_key(char *line, int begin, int len)
{
	char	*ptr;

	if ((ptr = ft_strsub(line, begin, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	return (ptr);
}

int				recognize_key(int *i, t_elem *current, char *line, int fd)
{
	int		len;
	char	*str;
	int		begin;

	if (DEBUG_PRINT)
		printf("ENTERRING RECOGNIZE KEY\n");
	len = 0;
	if (line[*i] != '"')
		return (0);
		//error_free_line(line, JSON_PARSING_ERROR);
	*i = *i + 1;
	begin = *i;
	while (line[*i] != '\0' && line[*i] != '"')
	{
			len++;
			*i = *i + 1;
	}
	// VERIFIER QUE STRING PAS VIDE
	if (line[*i] != '"' || len == 0)
		json_error(JSON_PARSING_ERROR);
		//return (0);
	*i = *i + 1;
	ignore_tab_and_spaces(&line, i, fd);
	if (line[*i] != ':')
		json_error(JSON_PARSING_ERROR);
		//return (0);
	*i = *i + 1;
	str = create_key(line, begin, len);
	if (DEBUG_PRINT)
		printf("KEY HAS BEEN FOUND : %s\n", str);
	current->key = str;
	return (1);
}
