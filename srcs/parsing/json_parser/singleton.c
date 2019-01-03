/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 21:28:24 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 14:57:47 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

static int			*get_ptr_line_number(void)
{
	static int		line_number = 0;

	return (&line_number);
}

int					get_line_number(void)
{
	return (*(get_ptr_line_number()));
}

void				set_line_number(int nbr)
{
	int				*line_number;

	line_number = get_ptr_line_number();
	(*line_number) = nbr;
}

void				add_line_number(int nbr)
{
	int				*line_number;

	line_number = get_ptr_line_number();
	(*line_number) = nbr + (*line_number);
}
