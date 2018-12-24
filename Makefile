# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/12/24 07:12:38 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/libftg/libftg.a \
	   ./libs/ft_printf/libftprintf.a \

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/libftg/includes/ -I ./libs/ft_printf/includes/

FLAGS = -Wall -Wextra -g3 -fsanitize=address -Ofast 

MLXFLAGS = -framework OpenGL -framework AppKit

OBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			main \
			errors \
			) \
		$(addprefix args_parsing/, \
			args_parsing \
			parse_args \
			usage \
			big_flag \
			small_flag \
			parse_mode \
			$(addprefix verbose/, \
				verbose_args \
				verbose_args_mode_bool \
				verbose_args_mode_multi \
				verbose_args_mode_multi1 \
				verbose_args_files \
			) \
		) \
		$(addprefix init/, \
			init \
			$(addprefix verbose/, \
			verbose_env \
			)\
		) \
	$(addprefix parsing/, \
		parsing \
		$(addprefix verbose/, \
			verbose_parsing \
			verbose_parsing_loops \
			verbose_parsing_printing \
		) \
		$(addprefix parsing_jsonrtv1/, \
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
			defaults \
		) \
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
			recognize_type \
		) \
	) \
	$(addprefix settings/, \
		settings \
		$(addprefix verbose/, \
			verbose_settings \
		) \
	) \
	\
	$(addprefix color/, color) \
	$(addprefix renderer/, printing) \
	$(addprefix singleton/, env_singleton scene_singleton camera_singleton renderer_singleton print_mode_singleton cursor_mode_singleton cursor_move_singleton win_singleton mlx_singleton args_singleton steps_singleton) \
	$(addprefix tools/, math_tools general_tools vector) \
	$(addprefix mlx_functions/, mlx) \
	$(addprefix parsing_tmp/, parsing structures_malloc) \
	$(addprefix raytracing/, raytracing ray) \
	$(addprefix raytracing/intersections/, cone cylinder plane sphere quadratic) \
	$(addprefix raytracing/normal/, normal cone cylinder plane sphere) \
	$(addprefix events/, event_listener) \
	$(addprefix verbose/, verbose debug_menu print_args print_obj debug print_env) \
	)) 


HEADERS = includes/rtv1.h \
		  includes/keys.h \
		  includes/args_parsing.h \
		  includes/rtv1_struct.h \
		  includes/json_parser.h \

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@make -C ./libs/mlx
	@make -C ./libs/libft
	@make -C ./libs/libftg
	@make -C ./libs/ft_printf
	@gcc -o $(NAME) $(FLAGS) $(MLX) $(MLXFLAGS) $(LIBS) $(OBJS) $(INCLUDES)

	
objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/core
	@mkdir -p objs/args_parsing/verbose
	@mkdir -p objs/init/verbose
	@mkdir -p objs/parsing/verbose
	@mkdir -p objs/settings/verbose
	@mkdir objs/parsing/parsing_tmp
	@mkdir objs/parsing/parsing_jsonrtv1
	@mkdir objs/parsing/json_parser
	@mkdir objs/color
	@mkdir objs/events
	@mkdir objs/mlx_functions
	@mkdir objs/singleton
	@mkdir objs/tools
	@mkdir objs/verbose
	@mkdir objs/renderer
	@mkdir objs/parsing_tmp
	@mkdir objs/raytracing
	@mkdir objs/raytracing/normal
	@mkdir objs/raytracing/intersections
	@mkdir objs/parsing_jsonrtv1/
	@mkdir objs/json_parser/

clean:
	@#	make -C ./libs/mlx clean
	@#	make -C ./libs/libft clean
	@#	make -C ./libs/libftg clean
	@#	make -C ./libs/ft_printf clean
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -f $(NAME)
	@#	rm -f $(MLX)
	@#	make -C ./libs/libft fclean
	@#	make -C ./libs/libftg fclean
	@#	make -C ./libs/ft_printf fclean

re:
	@$(MAKE) fclean
	@$(MAKE)
	@#	make -C ./libs/libft re
	@#	make -C ./libs/libftg re
	@#	make -C ./libs/mlx re
	@#	make -C ./libs/ft_printf re
