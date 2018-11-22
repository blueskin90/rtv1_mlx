/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:43:59 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 01:01:35 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_H
# define JSON_PARSER_H

# include "rtv1.h"
# include <fcntl.h>
# include <stdio.h>
typedef int bool;
#define true 1
#define false 0

typedef enum		s_type
{
	NOTYPE,
	INTEGER,
	STRING,
	FLOAT,
	BOOL,
	ASSOC_ARRAY,
	NUM_ARRAY,
	NULL_ELEM,
}					e_type;

typedef union		s_value
{
	int				inty;
	float			floaty;
	bool			booly;
	char			*stringy;
	void			*arrayi;
	void			*objecty;
	int				nully;
}					u_value;

typedef struct		s_elem
{
	char			main;
	char			closed;
	char			*key;
	e_type			type;
	u_value			value;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_key
{
	char			*name;
	t_type			type;
}					t_key;

/*
**	TO DELETE
*/
void		show_elem(t_elem *elem);
void		show_every_elem(t_elem *elem, int padding);

/*
** Utils
*/
int			update_line(int fd, char **line);
void		error_free_line(char *line, char *error);
int			ignore_tab_and_spaces(char **line, int *i, int fd);
char		end_of_value(char c);

/*
** Elem structures
*/
t_elem		*create_elem();
/*
**	Recognize elements
*/
t_elem		*json_recursive(int fd, char **line, int *i);
int			recognize_key(int *i, t_elem *current, char *line, int fd);
int			json_recognize_number(t_elem *current, char *line, int *i);
int			json_recognize_string(t_elem *current, char *line, int *i);
#endif
