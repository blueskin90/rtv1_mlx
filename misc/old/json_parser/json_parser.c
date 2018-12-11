/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 19:05:53 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void	json_parser(char *file)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(FD_FAIL);	
	if ((ret = ft_get_next_line(fd, &line)))
		ft_error(EMPTY_FILE);
	printf("%s\n", line);
}
