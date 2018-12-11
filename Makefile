# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2018/12/11 13:38:13 by cvermand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

MLX = ./libs/mlx/libmlx.a 

LIBS = ./libs/libft/libft.a \
	   ./libs/libftg/libftg.a

INCLUDES = -I includes/ -I ./libs/mlx/ -I ./libs/libft/includes/ -I ./libs/libftg/includes/

FLAGS = -Wall -Wextra -g3 -fsanitize=address -Ofast 

MLXFLAGS = -framework OpenGL -framework AppKit

# $(addprefix core/, main init tools copy_structures fct_structures test world_to_cam )  \
 	   $(addprefix utils/, print) \ 
	   #$(addprefix hooks/, event_listener) \
	   $(addprefix raytracer/, raytracing intersections colorize) 
OBJS = $(addprefix objs/, $(addsuffix .o, \
	   $(addprefix core/, main init tools debug structures_malloc singleton event_listener mlx intersections raytracing printing color ray normal float vector parsing errors) \
	   $(addprefix parsing/, \
	   parsing \
	   parse_scene \
	   parse_objects \
	   parse_object \
	   parse_light \
	   parse_aritmectif_values \
	   parse_cameras \
	   key_utils \
	   key_types_utils \
	   parse_vectors \
	   color_parsing \
	   init_camera \
	   init_light \
	   init_object \
	   required \
	   ) \
	   $(addprefix json_parser/, json_parser recognize_key elem_struct_functions \
	   recognize_number recognize_string print_elem_architecture \
		json_utils recognize_bool recognize_null recognize_array \
		recognize_object object_recursive array_recursive \
		recognize_type ) \
		))

all: $(NAME)

$(NAME): objs $(OBJS)
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
	@mkdir objs/parsing/
	@mkdir objs/json_parser/
#	@mkdir objs/raytracer
	#@mkdir objs/hooks
#	@mkdir objs/utils/
	#mkdir -p objs/core

clean:
#	make -C ./libs/mlx clean
#	make -C ./libs/libft clean
#	make -C ./libs/libftg clean
	@printf  "\033[1:32mCleaning object files -> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@rm -rf objs

fclean: clean
	@printf  "\033[1:32mCleaning binary -------> \033[91m$(NAME)\033[0m\033[1:32m:\033[0m%-16s\033[32m[✔]\033[0m\n"
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
