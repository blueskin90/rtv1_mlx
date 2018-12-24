/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:16:28 by cvermand          #+#    #+#             */
/*   Updated: 2018/12/16 16:52:46 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

void				*json_malloc(size_t size)
{
	void			*ptr;

	if (!(ptr = malloc(size)))
		ft_error(MALLOC_FAIL);
	ft_bzero(ptr, size);
	return (ptr);
}

char		end_of_value(char c)
{
	if (c == '\n' || c == ',' || c == ']' || c == '}' || c == '\0' || c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int			update_line(int fd, char **line)
{
	int		ret;

//	printf("NEW LINE\n");
	free((*line));
	(*line) = NULL;
	ret = ft_get_next_line(fd, line);
	return (ret);
}

void		error_free_line(char *line, char *error)
{
	free(line);
	line = NULL;
	ft_error(error);
}

int		ignore_tab_and_spaces(char **line, int *i, int fd)
{
	int ret;

	ret = 1;
	while ((*line)[*i] == '\t' || (*line)[*i] == ' ' || (*line)[*i] == '\0')
	{
		if ((*line)[*i] == '\0')
		{
			*i = 0;
			if ((ret = update_line(fd, line)) != 1)
			{
//				printf("END OF FILE\n");
				return (ret);
			}
		}
		else
			*i = *i + 1;
	}
//	printf("end ignore tab and spaces : %s c : %d i : %d ret : %d\n", 
//			*line, (*line)[*i], *i, ret);
	return (ret);
}
