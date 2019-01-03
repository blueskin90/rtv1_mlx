/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 22:20:22 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 19:54:30 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "json_parser.h"

int			main(int ac, char **av)
{
	t_elem		*elem;
		
	(void) ac;
	elem = json_parser(av[1]);
	ft_printf("NO ERRORS\n");
	return (1);
}
