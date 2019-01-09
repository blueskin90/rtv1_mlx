/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 00:43:10 by toliver           #+#    #+#             */
/*   Updated: 2019/01/09 17:56:02 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"



/*
static int			lst_fill(t_lst *lst, int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				read_ret;
	char			*tmp;

	if (lst->str == NULL)
	{
		if ((read_ret = read(fd, buf, BUFF_SIZE)) < 1)
			return (read_ret == 0 ? 0 : -1);
		if (!(lst->str = ft_strnew(0)))
			return (-1);
	}
	else if ((read_ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (-1);
	buf[read_ret] = '\0';
	if (!(tmp = ft_strjoin(lst->str, buf)))
		return (-1);
	free((lst->str));
	lst->str = tmp;
	tmp = NULL;
	if ((!(ft_strchr(lst->str, '\n'))) && read_ret > 0)
		return (lst_fill(lst, fd));
	return (1);
}

static t_lst		*lst_new(int fd)
{
	t_lst			*new;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

static int			line_split(t_lst *lst, char **line)
{
	char			*tmp;
	int				nl_pos;

	if (!(ft_strchr(lst->str, '\n')))
	{
		*line = lst->str;
		lst->str = NULL;
		if (ft_strlen(*line) > 0)
			return (1);
		return (0);
	}
	else
	{
		nl_pos = ft_strchr(lst->str, '\n') - lst->str;
		if (!(*line = ft_strsub(lst->str, 0, nl_pos)))
			return (-1);
		if (!(tmp = ft_strsub(lst->str, nl_pos + 1,
						ft_strlen(lst->str + nl_pos + 1))))
			return (-1);
		free(lst->str);
		lst->str = tmp;
		tmp = NULL;
	}
	return (1);
}

int					ft_get_next_line(const int fd, char **line)
{
	static t_lst	*lst = NULL;
	t_lst			*ptr;
	int				fill_ret;

	if (fd < 0 || (!lst && !(lst = lst_new(fd))))
		return (-1);
	ptr = lst;
	while (ptr->fd != fd && ptr->next != NULL)
		ptr = ptr->next;
	if (ptr->fd != fd)
	{
		if (!(ptr->next = lst_new(fd)))
			return (-1);
		ptr = ptr->next;
	}
	if ((fill_ret = lst_fill(ptr, fd)) < 1)
		return (fill_ret);
	return (line_split(ptr, line));
}

static t_lst		*lst_new(int fd)
{
	t_lst			*new;

	if (!(new = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}
*/

static int			elem_fill(t_lst *lst, int fd)
{
	char			buf[BUFF_SIZE + 1];
	int				read_ret;
	char			*tmp;

	while (!(ft_strchr(lst->str, '\n'))
			&& (read_ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[read_ret] = '\0';
		if (!(tmp = ft_strjoin(lst->str, buf)))
			return (0);
		free(lst->str);
		lst->str = tmp;
	}
	if (read_ret == -1)
		return (0);
	return (1);
}

static t_lst		*get_elem(t_lst **lst, int fd)
{
	t_lst			*ptr;

	if (!(*lst))
	{
		if (!((*lst) = (t_lst*)malloc(sizeof(t_lst))))
			return (NULL);
		(*lst)->fd = fd;
		if (!((*lst)->str = ft_strnew(0)))
			return (NULL);
		(*lst)->next = NULL;
		return (*lst);
	}
	ptr = *lst;
	while (ptr->fd != fd && ptr->next)
		ptr = ptr->next;
	if (ptr->fd == fd)
		return (ptr);
	if (!(ptr->next = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	ptr->next->fd = fd;
	if (!(ptr->next->str = ft_strnew(0)))
		return (NULL);
	ptr->next->next = NULL;
	return (ptr->next);
}

static int			split_and_return(t_lst *lst, char **line)
{
	char			*tmp;
	int				nl_pos;

	if (!(nl_pos = (int)ft_strchr(lst->str, '\n')))
	{
		*line = lst->str;
		lst->str = NULL;
		if (ft_strlen(*line) > 0)
			return (1);
		return (0);
	}
	nl_pos -= (int)lst->str;
	if (!(*line = ft_strsub(lst->str, 0, nl_pos)))
		return (-1);
	if (!(tmp = ft_strsub(lst->str, nl_pos + 1,
					ft_strlen(lst->str + nl_pos + 1))))
		return (-1);
	free(lst->str);
	lst->str = tmp;
	tmp = NULL;
	return (1);
}

int					ft_get_next_line(const int fd, char **line)
{
	static t_lst	*lst = NULL;
	t_lst			*ptr;

	if (fd < 0 || !(ptr = get_elem(&lst, fd)))
		return (-1);
	if (ptr->str == NULL)
		return (0);
	if (!ft_strchr(ptr->str, '\n') && !elem_fill(ptr, fd))
		return (-1);
	return (split_and_return(ptr, line));
}
