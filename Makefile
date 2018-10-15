# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/10/15 04:07:46 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a \
	  ./libs/libft/libft.a
INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/
FLAGS = -framework OpenGL -framework AppKit -Wall -Wextra #-g3 -fsanitize=address

OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(addprefix core/, main) \
		))

all: $(NAME)

$(NAME): objs $(OBJS)
	make -C ./libs/mlx
	make -C ./libs/libft
	gcc -o $(NAME) $(FLAGS) $(MLX) $(OBJS) $(INCLUDES)

objs/%.o: srcs/%.c
	gcc -o $@ -c $< $(FLAGS) $(INCLUDES)

objs:
	mkdir -p objs/events
	mkdir objs/core

clean:
	make -C ./libs/mlx clean
	make -C ./libs/libft clean
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX)
	make -C ./libs/libft fclean

re:
	$(MAKE) fclean
	$(MAKE)
	make -C ./libs/libft re
	make -C ./libs/mlx re
