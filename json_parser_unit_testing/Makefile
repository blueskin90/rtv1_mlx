# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: toliver <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/20 19:50:33 by toliver           #+#    #+#              #
#    Updated: 2019/01/06 23:13:40 by toliver          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = json_parser 

MLX = ../libs/mlx/libmlx.a 

LIBS = ../libs/libft/libft.a \
	   ../libs/libftg/libftg.a \
	   ../libs/ft_printf/libftprintf.a \

INCLUDES = -I includes/ -I ../libs/mlx/ -I ../libs/libft/includes/ \
		   -I ../libs/libftg/includes/ -I ../libs/ft_printf/includes/

FLAGS = -Wall -Wextra -g3 -fsanitize=address -Ofast  

MLXFLAGS = -framework OpenGL -framework AppKit

OBJS = $(addprefix objs/, $(addsuffix .o, \
		$(addprefix core/, \
			main \
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
) 


HEADERS = includes/json_parser.h \

all: $(NAME)

$(NAME): objs $(OBJS) $(HEADERS)
	@printf  "\033[92m\033[1:32mCompiling -------------> \033[91m$(NAME)\033[0m:\033[0m%-16s\033[32m[✔]\033[0m\n"
	@make -C ../libs/mlx
	@make -C ../libs/libft
	@make -C ../libs/libftg
	@make -C ../libs/ft_printf
	@gcc -o $(NAME) $(FLAGS) $(MLX) $(MLXFLAGS) $(LIBS) $(OBJS) $(INCLUDES)

	
objs/%.o: srcs/%.c
	@printf  "\033[1:92mCompiling $(NAME)\033[0m %-31s\033[32m[$<]\033[0m\n" ""
	@gcc -o $@ -c $< $(FLAGS) $(INCLUDES)
	@printf "\033[A\033[2K"

objs:
	@mkdir -p objs/core
	@mkdir -p objs/json_parser/

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
