# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvermand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:00:34 by cvermand          #+#    #+#              #
#    Updated: 2018/04/21 17:40:03 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmatrice.a

CC			= gcc
FLAGS		= -Wall -Werror -Wextra -g3
_SRC		= init_rotation_matrix.c init_scale_matrix.c \
			  init_translation_matrix.c matrix_multiplication.c \
			  create_new_matrix.c show_matrix.c show_vertex.c\
			  create_new_vertex.c show_vector.c \
			  create_new_vector.c magnitude_vector.c normalize_vector.c \
			  add_vectors.c sub_vectors.c opposite_vector.c\
			  scalarproduct_vector.c dotproduct_vectors.c \
			  crossproduct_vectors.c cos_vectors.c \
			  create_projection_struct.c init_projection_matrix.c\
			  init_vector.c init_vertex.c
_HEADER		= libmatrice.h

SRC_DIR		= .
HEADER_DIR	= includes
SRC			= $(addprefix $(SRC_DIR)/, $(_SRC))
HEADER		= $(addprefix $(HEADER_DIR)/, $(_HEADER))
BIN 		= $(SRC:.c=.o)
RM			= /bin/rm

all : $(NAME)

$(NAME) : $(BIN) $(HEADER)
	ar rc $(NAME) $(BIN)
	ranlib $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I includes/

clean : 
	rm -f $(BIN)

fclean : clean
	rm -r $(NAME)

re :
	make fclean
	make
