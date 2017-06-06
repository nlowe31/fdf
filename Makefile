# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlowe <nlowe@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/17 21:11:30 by nlowe             #+#    #+#              #
#    Updated: 2017/06/06 15:46:41 by nlowe            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
MLX = minilibx/libmlx.a
LIBFT = libft/libft.a

SRC_PATH = src
SRC_NAME = main.c \
			fdf.c \
			images.c \
			parsing.c \
			verification.c \

OBJ_PATH = obj
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH = libft
MLX_PATH = minilibx

CC = gcc
CFLAGS = -Werror -Wall -Wextra
IFLAGS = -I./includes
LFLAGS = -Llibft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	@echo "[make] fdf: Compiling..."
	@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $@ $^
	@echo "\033[92m----------------------\n|    fdf  compiled   |\n|       @nlowe       |\n----------------------\033[0m"

$(LIBFT):
	@make -C$(LIBFT_PATH)

$(MLX):
	@make -C$(MLX_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $^

clean:
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)
	# @make clean -C$(LIBFT_PATH)
	@make clean -C $(MLX_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C$(LIBFT_PATH)
	@make clean -C $(MLX_PATH)

re: fclean all

.PHONYL: all, clean, fclean, re
