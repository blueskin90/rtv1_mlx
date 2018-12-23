/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 21:42:09 by toliver           #+#    #+#             */
/*   Updated: 2018/12/23 03:11:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_parsing.h"

void			parse_arguments(int ac, char **av, t_args *args)
{
	int			i;

	i = 1;
	if (ac == 1)
		return ;
	while (i < ac)
	{
		if (av[i][0] != '-')
			break ;
		if (ft_strcmp(av[i], "--") == 0)
		{
			i++;
			break ;
		}
		else if (ft_strncmp(av[i], "--", 2) == 0)
			parse_bigflag(av[i] + 2, args);
		else if (av[i][0] == '-')
			parse_smallflag(av[i] + 1, args);
		i++;
	}
	if (i < ac)
		args->files = av + i;
}
