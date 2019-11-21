# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksticks <ksticks@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 20:27:05 by ksticks           #+#    #+#              #
#    Updated: 2019/09/25 15:44:59 by edrowzee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fdf
FLAGS = #-Wall -Wextra -Werror
SRC_ASCII = \
		ascii/main.c \
		ascii/line.c \
		ascii/ascii.c

SRC_MLX = \
		src/main.c \
		src/line.c

SRC = $(SRC_MLX) \
		src/app.c \
		src/controller.c \
		src/camera.c \
		src/mesh_read.c \
		src/mesh.c \
		src/panel.c

OPTION = -I. -Ilibft -Iminilibx_macos
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : libft/libft.a minilibx_macos/libmlx.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(OPTION) -L minilibx_macos/ -lmlx -L libft/ -lft -framework OpenGL -framework AppKit
#	@$(CC) -o $(NAME) $(OBJ) $(OPTION) -L minilibx_macos/ -L libft/ -lft

%.o: %.c
	@echo compile $(<) "->" $(<:.c=.o)
	$(CC) $(FLAGS) -c $(<) -o $(<:.c=.o) $(OPTION)

libft/libft.a :
	make -C libft/

minilibx_macos/libmlx.a :
#	@echo skip mac
	make -C minilibx_macos

run : $(NAME)
	@./$(NAME)

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

re : fclean all
