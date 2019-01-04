# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2019/01/04 18:34:36 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/libftg/libftg.a \
	   ./libs/ft_printf/libftprintf.a \

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/libftg/includes/ -I ./libs/ft_printf/includes/

FLAGS = -Wall -Wextra -g3 -Ofast#-fsanitize=address

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
		$(addprefix parsing_tmp/, \
			parsing \
			structures_malloc \
		) \
		$(addprefix verbose/, \
			verbose_parsing \
			verbose_parsing_loops \
			verbose_parsing_printing \
		) \
		$(addprefix rtv1_parsing/, \
			defaults \
			init_object \
			key_utils \
			key_types_utils \
			key_types_number \
			parsing \
			parse_scene \
			parse_utils \
			parse_objects \
			parse_object \
			parse_light \
			parse_arithmetic_values \
			parse_object_direction \
			parse_object_direction_extension \
			parse_cameras \
			parse_vectors \
			parse_colors \
			color_utils \
			required \
		) \
		$(addprefix json_parser/, \
			json_parser \
			recognize_key \
			elem_struct_functions \
			recognize_number \
			recognize_string \
			print_elem_architecture \
			json_errors \
			singleton \
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
		ray \
		renderer_init \
		$(addprefix verbose/, \
			verbose_settings \
		) \
	) \
	$(addprefix running/, \
		running \
		$(addprefix raytracing/, \
			raytracing \
			$(addprefix primitives/, \
				$(addprefix cone/, \
					intersect \
					normal \
				) \
				$(addprefix cylinder/, \
					intersect \
					normal \
				) \
				$(addprefix plane/, \
					intersect \
					normal \
				) \
				$(addprefix sphere/, \
					intersect \
					normal \
				) \
				common \
			) \
			$(addprefix stack/, \
				stack_raytracing \
			) \
			$(addprefix malloc/, \
				malloc_raytracing \
			) \
			$(addprefix common/, \
				ray_shooting \
				ray_light_shooting \
				reflect \
			) \
		) \
		$(addprefix verbose/, \
			verbose_running \
		) \
	) \
	$(addprefix printing/, \
		printing \
		$(addprefix verbose/, \
			verbose_printing \
		) \
	) \
	$(addprefix loop/, \
		loop \
		$(addprefix verbose/, \
			verbose_loop \
		) \
	) \
	\
	$(addprefix tools/, \
		math_tools \
		general_tools \
		vector \
		mlx_tools \
		print_tools \
		$(addprefix colors_handling/, \
			colors_init \
			rgb_functions \
		) \
	) \
	\
	)) 


HEADERS = includes/rtv1.h \
		  includes/keys.h \
		  includes/args_parsing.h \
		  includes/rtv1_struct.h \
		  includes/json_parser.h \
		  includes/colors.h \
		  includes/json_parser_errors.h \
		  includes/libft_errors.h \
		  includes/mlx_errors.h \
		  includes/rtv1_errors.h \
		  includes/rtv1_required_information.h \

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
	@mkdir objs/parsing/parsing_tmp
	@mkdir objs/parsing/rtv1_parsing
	@mkdir objs/parsing/json_parser
	@mkdir -p objs/settings/verbose
	@mkdir -p objs/running/verbose
	@mkdir -p objs/running/raytracing/malloc
	@mkdir objs/running/raytracing/stack
	@mkdir -p objs/running/raytracing/primitives/cone
	@mkdir objs/running/raytracing/primitives/cylinder
	@mkdir objs/running/raytracing/primitives/plane
	@mkdir objs/running/raytracing/primitives/sphere
	@mkdir objs/running/raytracing/common
	@mkdir -p objs/printing/verbose
	@mkdir -p objs/loop/verbose
	@mkdir -p objs/tools/colors_handling

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
