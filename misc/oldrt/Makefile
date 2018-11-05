# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cvermand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:34:00 by cvermand          #+#    #+#              #
#    Updated: 2018/04/21 17:44:31 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= rtv1

CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra -g3
_SRC		=	main.c init_env.c exit.c ratio.c sphere.c
_HEADER		=	rtv1.h

_LIBFT		=	libft.a
_MATRIX		=	libmatrice.a
_MLX		= 	libmlx.a

SRC_DIR		=	src
HEADER_DIR	=	includes
LIB_DIR		=	libft
MATRIX_DIR	=	libmatrice
MLX_DIR		=	minilibx_macos

SRC			=	$(addprefix $(SRC_DIR)/, $(_SRC))
HEADER		=	$(addprefix $(HEADER_DIR)/, $(_HEADER))
LIBFT		=	$(addprefix $(LIB_DIR)/, $(_LIBFT))
MATRIX		=	$(addprefix $(MATRIX_DIR)/, $(_MATRIX))
MLX			=	$(addprefix $(MLX_DIR)/, $(_MLX))

BIN 		=	$(SRC:.c=.o)
RM			=	/bin/rm

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(MATRIX) $(BIN) $(HDR)
	@$(CC) $(CFLAGS) -o $(NAME) $(BIN) -framework OpenGL -framework AppKit \
	-L$(LIB_DIR) -lft -L$(MLX_DIR) -L$(MATRIX_DIR) -lmatrice \
	-lmlx -lm -D_REENTRANT -lpthread
	@echo "$(NAME) : $(_GREEN)Done$(_END)"

$(LIBFT):
	@make -C $(LIB_DIR)

$(MLX):
	@make -C $(MLX_DIR)

$(MATRIX):
	@make -C $(MATRIX_DIR)

%.o : %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@ -I includes/

clean:
	@make fclean -C $(LIB_DIR)
	@make fclean -C $(MLX_DIR)
	@make fclean -C $(MATRIX_DIR)
	@/bin/rm -f $(BIN)
	@echo "RTV1 clean : $(_GREEN)Done$(_END)"

fclean: clean
	@/bin/rm -f $(FRACTOL)
	@echo "RTV1 fclean : $(_GREEN)Done$(_END)"

re:
	@make fclean
	@make

.PHONY: all clean fclean re


