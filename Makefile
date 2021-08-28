# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/28 18:34:20 by agirona           #+#    #+#              #
#    Updated: 2021/08/28 18:41:28 by agirona          ###   ########lyon.fr    #
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

LIBFT = dependency/libft/libft.a

MLX = dependency/mlx/libmlx.a

CFLAGS	= -Wall -Wextra -Werror -I $(INC)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INC)
	gcc $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME) : 	$(OBJS_PATH) $(LIBFT) $(MLX)
			gcc $(OBJS_PATH) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT) :
			$(MAKE) -C dependency/libft

$(MLX) :
			$(MAKE) -C dependency/mlx

clean:
			rm -f $(OBJS_PATH)
			$(MAKE)	-C dependency/libft clean
			$(MAKE)	-C dependency/mlx clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE)	-C dependency/libft fclean

re:			fclean all

.PHONY:		all clean fclean re
