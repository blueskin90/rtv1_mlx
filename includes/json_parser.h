/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:43:59 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 17:50:44 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_H
# define JSON_PARSER_H

# include "json_parser_errors.h"
# include "libft.h"
# include "libftprintf.h"
# include <fcntl.h>
# include <stdio.h>
typedef int bool;
# define true 1
# define false 0
# define DEBUG_PRINT 0
# define PRINT_TREE 1

typedef enum	e_json_data
{
	NOTYPE,
	INTEGER,
	STRING,
	FLOAT,
	BOOL,
	OBJECT,
	NULL_ELEM,
	ARRAY,
}				t_json_data;

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
	t_json_data		type;
	u_value			value;
	struct s_elem	*next;
}					t_elem;




/*
**	TO DELETE
*/
void		show_elem(t_elem *elem);
void		show_one_elem(t_elem *elem, int padding);
void		show_every_elem(t_elem *elem, int padding);

/*
** JSON PARSER
*/
t_elem				*json_parser(char *file);
/*
** Utils
*/
int			update_line(int fd, char **line);
void		error_free_line(char *line, char *error);
int			ignore_tab_and_spaces(char **line, int *i, int fd, char end);
char		end_of_value(char c);
void		json_error(char *error);

/*
** Elem structures
*/
t_elem		*create_elem();
u_value		set_value_of_type(t_json_data type, void *defaulty);
t_elem		*create_init_elem(char *key, t_json_data type, void *value);
/*
**	Recognize elements
*/
t_elem		*json_recursive(int fd, char **line, int *i);
t_elem		*array_recursive(int fd, char **line, int *i);
int			recognize_type(t_elem *current, char **line, int *i);
int			recognize_key(int *i, t_elem *current, char *line, int fd);
int			json_recognize_number(t_elem *current, char *line, int *i);
int			json_recognize_string(t_elem *current, char *line, int *i);
int			json_recognize_bool(t_elem *current, char *line, int *i);
int			json_recognize_null(t_elem *current, char *line, int *i);
int			json_recognize_array(t_elem *current, char **line, int *i, int fd);
int			json_recognize_object(t_elem *current, char **line, int *i, int fd);

/*
**	SINGLETONS
*/
int			get_line_number();
void		set_line_number(int nbr);
void		add_line_number(int nbr);
/*
** Generic functions
*/

void				*json_malloc(size_t size);
void				ft_error(char *str);
#endif
