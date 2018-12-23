# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/12/23 03:20:05 by toliver          ###   ########.fr        #
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
	$(addprefix core/, main errors) \
	$(addprefix args_parsing/, args_parsing parse_args usage big_flag small_flag print) \
	$(addprefix init/, init print) \
	\
	$(addprefix renderer/, printing) \
	$(addprefix color/, color) \
	$(addprefix singleton/, env_singleton scene_singleton camera_singleton renderer_singleton print_mode_singleton cursor_mode_singleton cursor_move_singleton win_singleton mlx_singleton args_singleton steps_singleton) \
	$(addprefix tools/, math_tools general_tools vector) \
	$(addprefix mlx_functions/, mlx) \
	$(addprefix parsing_tmp/, parsing structures_malloc) \
	$(addprefix raytracing/, raytracing ray) \
	$(addprefix raytracing/intersections/, cone cylinder plane sphere quadratic) \
	$(addprefix raytracing/normal/, normal cone cylinder plane sphere) \
	$(addprefix events/, event_listener) \
	$(addprefix debug/, debug debug_menu print_obj) \
	$(addprefix verbose/, verbose) \
	$(addprefix parsing/, \
	parsing \
	parse_scene \
	parse_utils \
	parse_objects \
	parse_object \
	parse_light \
	parse_arithmetic_values \
	parse_object_direction \
	parse_cameras \
	key_utils \
	key_types_utils \
	parse_vectors \
	parse_colors \
	init_camera \
	init_light \
	init_object \
	required \
	defaults) \
	$(addprefix json_parser/, \
	json_parser \
	recognize_key \
	elem_struct_functions \
	recognize_number \
	recognize_string \
	print_elem_architecture \
	json_utils \
	recognize_bool \
	recognize_null \
	recognize_array \
	recognize_object \
	object_recursive \
	array_recursive \
	recognize_type)))

HEADERS = includes/rtv1.h \
		  includes/keys.h \
		  includes/args_parsing.h \
		  includes/rtv1_struct.h \

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@make -C ./libs/mlx
	@make -C ./libs/libft
	@make -C ./libs/libftg
	@gcc -o $(NAME) $(FLAGS) $(MLX) $(MLXFLAGS) $(LIBS) $(OBJS) $(INCLUDES)

	
objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/core
	@mkdir objs/color
	@mkdir objs/args_parsing
	@mkdir objs/debug
	@mkdir objs/events
	@mkdir objs/init
	@mkdir objs/mlx_functions
	@mkdir objs/singleton
	@mkdir objs/tools
	@mkdir objs/verbose
	@mkdir objs/renderer
	@mkdir objs/parsing_tmp
	@mkdir objs/raytracing
	@mkdir objs/raytracing/normal
	@mkdir objs/raytracing/intersections
	@mkdir objs/parsing/
	@mkdir objs/json_parser/

clean:
	@#	make -C ./libs/mlx clean
	@#	make -C ./libs/libft clean
	@#	make -C ./libs/libftg clean
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME)
	@#	rm -f $(MLX)
	@#	make -C ./libs/libft fclean
	@#	make -C ./libs/libftg fclean

re:
	@$(MAKE) fclean
	@$(MAKE)
	@#	make -C ./libs/libft re
	@#	make -C ./libs/libftg re
	@#	make -C ./libs/mlx re
