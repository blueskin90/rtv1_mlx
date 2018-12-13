# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/12/13 12:11:54 by toliver          ###   ########.fr        #
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
	   $(addprefix core/, main) \
	   $(addprefix renderer/, printing) \
	   $(addprefix color/, color) \
	   $(addprefix singleton/, env_singleton scene_singleton camera_singleton renderer_singleton print_mode_singleton cursor_mode_singleton cursor_move_singleton win_singleton mlx_singleton) \
	   $(addprefix tools/, math_tools general_tools vector) \
	   $(addprefix mlx_functions/, mlx) \
	   $(addprefix initialization/, init) \
	   $(addprefix parsing_tmp/, parsing structures_malloc) \
	   $(addprefix raytracing/, raytracing ray) \
	   $(addprefix raytracing/intersections/, cone cylinder plane sphere quadratic) \
	   $(addprefix raytracing/normal/, normal cone cylinder plane sphere) \
	   $(addprefix events/, event_listener) \
	   $(addprefix debug/, debug debug_menu print_obj) \
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
	mkdir objs/color
	mkdir objs/debug
	mkdir objs/events
	mkdir objs/initialization
	mkdir objs/mlx_functions
	mkdir objs/singleton
	mkdir objs/tools
	mkdir objs/renderer
	mkdir objs/parsing_tmp
	mkdir objs/raytracing
	mkdir objs/raytracing/normal
	mkdir objs/raytracing/intersections

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
