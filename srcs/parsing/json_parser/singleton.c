/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 21:28:24 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/24 21:28:31 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "json_parser.h"

static int			*get_ptr_line_number()
{
	static int		line_number = 0;

	return (&line_number);
}

int			get_line_number()
{
	return (*(get_ptr_line_number()));
}

void		set_line_number(int nbr)
{
	int		*line_number;

	line_number = get_ptr_line_number();
	(*line_number) = nbr;
}

void		add_line_number(int nbr)
{
	int		*line_number;

	line_number = get_ptr_line_number();
	(*line_number) = nbr + (*line_number);
}
