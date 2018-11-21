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

void		update_line(int fd, char *line)
{
	
	free(line);
	line = NULL;
	ft_get_next_line(fd, &line);
		
}

void		ignore_tab_and_spaces(char *line, int *i, int fd)
{
	while (line[*i] == "\t" || line[*i] == ' ')
		*i = *i + 1;
	if (line[*i] == "\n")

}

t_elem		*json_recursive(int fd, char *line, int i)
{
	t_elem	current;
	while (line[i])
	{
		//recognize key
		//recognize string
		//recognize object
		//recognize array
		//recognize integer
		//recognize float
		//recognize null
	}
}

void	json_parser(char *file)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(FD_FAIL);	
	if ((ret = ft_get_next_line(fd, &line)) != 1)
		ft_error(EMPTY_FILE);
	printf("size elem : %d\n", sizeof(t_elem));
	printf("%s\n", line);
}
