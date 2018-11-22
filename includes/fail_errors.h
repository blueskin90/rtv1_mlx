/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail_errors.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:28:10 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/22 01:10:20 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAIL_ERRORS_H
# define FAIL_ERRORS_H

# define MALLOC_FAIL "Malloc failed\n"
# define MLX_FAIL "Couldn't start MLX\n"
# define WINDOW_FAIL "Couldn't open a new window\n"
# define MLX_IMG_FAIL "MLX couldn't get a new image\n"

/*
** FILE OPEN READ WRITE ERRORS
*/
# define FD_FAIL "Could not open file\n"
# define EMPTY_FILE	"file is empty\n"

/*
** ERROR PARSING
*/
# define JSON_PARSING_ERROR "JSON HAS WRONG FORMAT\n"
# define KEY_NOT_FOUND "KEY WAS NOT RECOGNIZED\n"

#endif
