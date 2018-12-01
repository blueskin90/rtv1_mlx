/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:43:59 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/19 19:05:08 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_PARSER_H
# define JSON_PARSER_H

# include "rtv1.h"
# include <fcntl.h>
typedef int bool;
#define true 1
#define false 0

typedef enum		s_type
{
	INTEGER,
	FLOAT,
	BOOL,
	ASSOC_ARRAY,
	NUM_ARRAY,
	NULL_ELEM,

}					e_type;

typedef struct		s_elem
{
	char			main;
	char			closed;
	char			*key;
	e_type			type;
	void			*value;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_key
{
	char			*name;
	t_type			type;
}					t_key;
#endif
