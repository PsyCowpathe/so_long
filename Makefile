# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:34:20 by agirona           #+#    #+#              #
#    Updated: 2021/09/07 21:49:38 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRCS = so_long.c get_map.c parsing.c event.c physics.c enemy.c error.c \
	   mlx_utility.c parsing_utility.c physics_utility.c print_map.c \
	   utility.c

SRCS_DIR = src

OBJS = $(SRCS:.c=.o)

OBJS_DIR = obj

OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

INC	= include

MAKE = make -C

LIBRARY = dependency/libft/libft.a dependency/mlx/libmlx.a

FRAMEWORK = -framework OpenGL -framework Appkit

CFLAGS	= -Wall -Wextra -Werror -I $(INC)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC)/so_long.h
	gcc $(CFLAGS) -c $< -o $@

all: create_obj_dir lib $(NAME)

lib:
			$(MAKE) ./dependency/libft/
			$(MAKE) ./dependency/mlx/

$(NAME) :	$(LIBRARY) $(OBJS_PATH)
			gcc $(FRAMEWORK) $(OBJS_PATH) $(LIBRARY) -o $(NAME)

create_obj_dir :
			mkdir -p obj

clean:
			rm -f $(OBJS_PATH)
			$(MAKE) ./dependency/libft clean
			$(MAKE) ./dependency/mlx clean

fclean:		clean
			rm -f $(NAME)
			rm -rf obj
			$(MAKE) ./dependency/libft fclean

re:			fclean all

.PHONY:		all lib create_obj_dir clean fclean re
