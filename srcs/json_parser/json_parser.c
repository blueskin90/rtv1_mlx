/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 17:03:05 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 01:02:11 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_parser.h"

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

	printf("NEW LINE\n");
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
				printf("END OF FILE\n");
				return (ret);
			}
		}
		else
			*i = *i + 1;
	}
	printf("end ignore tab and spaces : %s c : %d i : %d ret : %d\n", 
			*line, (*line)[*i], *i, ret);
	return (ret);
}

t_elem		*json_recursive(int fd, char **line, int *i)
{
	t_elem	*current;
	char	type_found;

	type_found = 0;
	current = create_elem();
	printf("line BEGIN ELEMENT : %s i : %d\n", &((*line)[*i]), *i);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	if ((recognize_key(i, current, *line, fd)) == 0)
		error_free_line(*line, KEY_NOT_FOUND);
	printf("line ibefore cleaning recur : %s i : %d\n", &((*line)[*i]), *i);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	printf("line before number  recur : %s i : %d\n", &((*line)[*i]), *i);
	if ((type_found = json_recognize_number(current, *line, i)) == 1)
		type_found = 1;
	else if ((type_found = json_recognize_string(current, *line, i)) == 1)
		type_found = 1;
	else 
		ft_error(JSON_PARSING_ERROR);
	// recognize type : 
	printf("line before cleaning  recur : %s i : %d\n", &((*line)[*i]), *i);
	if ((ignore_tab_and_spaces(line, i, fd) != 1))
		return (current);
	printf("line before sibling  recur : %s i : %d\n", &((*line)[*i]), *i);
	while ((*line)[*i] == ',')
	{
		*i = *i + 1;
		printf("line before recursive : %s i : %d\n", &((*line)[*i]), *i);
		current->next = json_recursive(fd, line, i);
		printf("line after recursive before cleaning: %s i : %d\n", 
				&((*line)[*i]), *i);
		if ((ignore_tab_and_spaces(line, i, fd) != 1))
			return (current);
		printf("line after recursive cleaning : %s i : %d\n",
				&((*line)[*i]), *i);
	}
	printf("line recur : %s i : %d\n",
				&((*line)[*i]), *i);
	if ((*line)[*i] != '}' || ((*line)[*i] == '}' && (*line)[*i + 1] != '\0'))
		ft_error(JSON_PARSING_ERROR);
	current->closed = 1;
	//while (line[i])
	//{

	//recognize key
	//recognize string
	//recognize object
	//recognize array
	//recognize integer
	//recognize float
	//recognize null
	//}
	return (current);
}

void	json_parser(char *file)
{
	int		fd;
	char	*line;
	int		ret;
	t_elem	*begin;
	int		x;

	begin = NULL;
	line = NULL;
	x = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error(FD_FAIL);	
	if ((ret = ft_get_next_line(fd, &line)) != 1)
		ft_error(EMPTY_FILE);
	printf("size elem : %lu\n", sizeof(t_elem));
	printf("%s\n", line);
	if (line[0] == '{')
		begin = json_recursive(fd, &line, &x);
	show_every_elem(begin, 0);
}
