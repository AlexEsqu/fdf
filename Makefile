# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkling <mkling@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 14:56:12 by mkling            #+#    #+#              #
#    Updated: 2024/10/28 17:46:10 by mkling           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

SRC_DIR		= ./src

OBJ_DIR		= ./obj

INC			= -I./lib/libft \
			-I./lib/minilibx

SRCS		= main.c \
			display.c \
			parse.c \
			trace.c \
			render.c \
			rotate.c \
			color.c \
			input.c \
			preset.c \
			center.c \
			gradient.c \
			elevation.c \
			error.c

LIBS		= ./lib/libft/libft.a \
			./lib/minilibx/libmlx.a \
			-L/usr/lib -lX11 -lXext -lm -lz

OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(addprefix $(SRC_DIR)/, $(SRCS)))

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -O3


all:		$(NAME)

$(NAME):	$(OBJS) ./inc/fdf.h
			$(MAKE) -C ./lib/libft
			$(MAKE) -C ./lib/minilibx
			$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(SRC_DIR)/, $(SRCS)) $(LIBS)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					mkdir -p $(OBJ_DIR)
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

debug:		$(OBJS)
			$(MAKE) -C ./lib/libft
			$(MAKE) -C ./lib/minilibx
			$(CC) $(CFLAGS) -g -o $(NAME) $(addprefix $(SRC_DIR)/, $(SRCS)) $(LIBS)

clean:
			$(MAKE) -C ./lib/libft clean
			$(MAKE) -C ./lib/minilibx clean
			rm -rf $(OBJ_DIR)

fclean:		clean
			rm -rf $(NAME)
			$(MAKE) -C ./lib/libft fclean

re:			fclean all

.PHONY:		all clean fclean re debug
