/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:00:31 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:36:05 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

/*
** 0 : NOP
** 1: INT
** 2 : FLOAT
*/
int		valid_number(char *line, int i, int *len)
{
	char	coma;
	int		begin;
	int		i_tmp;

	i_tmp = i;
	coma = 0;
	begin = i_tmp;
	if (line[i_tmp] == '-' || line[i_tmp] == '+')
		i_tmp = i_tmp + 1;
	while (ft_isdigit(line[i_tmp]) && line[i_tmp] != '\0')
		i_tmp = i_tmp + 1;
	if (line[i_tmp] == '.')
	{
		coma = 1;
		i_tmp = i_tmp + 1;
		while (ft_isdigit(line[i_tmp]) && line[i_tmp] != '\0')
			i_tmp = i_tmp + 1;
	}
	*len = i_tmp - begin;
	if (!(end_of_value(line[i_tmp])))
		return (0);
	else if (coma)
		return (2);
	else 
		return (1);
}

int		json_recognize_number(t_elem *current, char *line, int *i)
{
	int				x;
	float			dec;
	int				len;
	char			type;
	char			*tmp;

	x = 0;
	if (DEBUG_PRINT)
		printf("ENTERING NUMBER PARSER i : %d\n", *i);
	len = 0;
	if (!(type = valid_number(line, *i, &len)) || len == 0)
	{
		if (DEBUG_PRINT)
			printf(" i : %d\n", *i);
		if (DEBUG_PRINT)
			printf("value is not a number : %d\n", type);
		return (0);	
	}
	if ((tmp = ft_strsub(line, *i, (size_t)len)) == NULL)
		json_error(MALLOC_FAIL);
	if (type == 1)
	{
		x = ft_atoi(tmp);
		if (DEBUG_PRINT)
			printf("x : %d\n", x);
		free(tmp);
		current->value.inty = x;
		current->type = INTEGER;
		if (DEBUG_PRINT)
			printf("ELEM IS INTEGER NUMBER : %d len : %d s : %s\n", x, len, &line[*i]);
		*i = *i + len;
		return (current->type);
	}
	if (type == 2)
	{
		//printf("str before atof : %s\n", tmp);
		dec = ft_atof(tmp);
		if (DEBUG_PRINT)
			printf("x : %f\n", dec);
		free(tmp);
		current->value.floaty = dec;
		current->type = FLOAT;
		if (DEBUG_PRINT)
			printf("ELEM IS FLOAT NUMBER : %d\n", x);
		*i = *i + len;
		return (current->type);
	}
	return (0);
}
