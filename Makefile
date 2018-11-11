# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/11/11 00:05:02 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/libftg/libftg.a

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/libftg/includes/

FLAGS = -framework OpenGL -framework AppKit -Wall -Wextra -g3 -fsanitize=address

OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(addprefix core/, main init tools copy_structures fct_structures test world_to_cam ) \
	   $(addprefix utils/, print) \
	   $(addprefix hooks/, event_listener) \
	   $(addprefix raytracer/, raytracing intersections colorize) \
		))

all: $(NAME)

$(NAME): objs $(OBJS)
	make -C ./libs/mlx
	make -C ./libs/libft
	make -C ./libs/libftg
	gcc -o $(NAME) $(FLAGS) $(MLX) $(LIBS) $(OBJS) $(INCLUDES)

objs/%.o: srcs/%.c
	gcc -o $@ -c $< $(FLAGS) $(INCLUDES)

objs:
	mkdir -p objs/core
	mkdir objs/raytracer
	mkdir objs/hooks
	mkdir objs/utils/

clean:
	make -C ./libs/mlx clean
	make -C ./libs/libft clean
	make -C ./libs/libftg clean
	rm -rf objs

fclean: clean
	rm -f $(NAME)
	rm -f $(MLX)
	make -C ./libs/libft fclean
	make -C ./libs/libftg fclean

re:
	$(MAKE) fclean
	$(MAKE)
	make -C ./libs/libft re
	make -C ./libs/libftg re
	make -C ./libs/mlx re
