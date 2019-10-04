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
FLAGS = -Wall -Wextra -Werror
SRC = src/main.c \
		src/line.c
#		src/t_vector.c \
#		src/t_matrix.c
OPTION = -I. -Ilibft -Iminilibx_macos
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : libft/libft.a minilibx_macos/libmlx.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(OPTION) -L minilibx_macos/ -lmlx -L libft/ -lft -framework OpenGL -framework AppKit

run : $(NAME)
	@./fdf

%.o: %.c libft/libft.a
	@echo compile $(<) "->" $(<:.c=.o)
	@$(CC) $(FLAGS) -c $(<) -o $(<:.c=.o) $(OPTION)

libft/libft.a :
	make -C libft/

minilibx_macos/libmlx.a :
	make -C minilibx_macos

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

re : fclean all
