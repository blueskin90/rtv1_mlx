# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/12/10 17:43:57 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/libftg/libftg.a

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/libftg/includes/

FLAGS = -Wall -Wextra -g3 -fsanitize=address -Ofast 

MLXFLAGS = -framework OpenGL -framework AppKit


OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(addprefix core/, main init tools debug structures_malloc singleton event_listener mlx intersections raytracing printing color ray normal float vector parsing test) \
		))

HEADERS = includes/rtv1.h \
		  includes/fail_errors.h \
		  includes/keys.h

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	make -C ./libs/mlx
	make -C ./libs/libft
	make -C ./libs/libftg
	gcc -o $(NAME) $(FLAGS) $(MLX) $(MLXFLAGS) $(LIBS) $(OBJS) $(INCLUDES)

objs/%.o: srcs/%.c $(HEADERS)
	gcc -o $@ -c $< $(FLAGS) $(INCLUDES)

objs:
	mkdir -p objs/core

clean:
#	make -C ./libs/mlx clean
#	make -C ./libs/libft clean
#	make -C ./libs/libftg clean
	rm -rf objs

fclean: clean
	rm -f $(NAME)
#	rm -f $(MLX)
#	make -C ./libs/libft fclean
#	make -C ./libs/libftg fclean

re:
	$(MAKE) fclean
	$(MAKE)
#	make -C ./libs/libft re
#	make -C ./libs/libftg re
#	make -C ./libs/mlx re
