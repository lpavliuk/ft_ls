# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 16:04:15 by opavliuk          #+#    #+#              #
#    Updated: 2018/05/14 13:49:27 by opavliuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

CC=gcc 
CFLAGS=-O3 -Wall -Werror -Wextra
SRC=./src/check_flags.c \
	./src/check_mode.c \
	./src/ft_strjoin_dir.c \
	./src/lists.c \
	./src/output_mode.c \
	./src/read_info.c \
	./src/recursion.c \
	./src/sort_lists.c \
	./src/staff.c \
	./src/main.c
OBJ=$(SRC:.c=.o)
NAME=ft_ls
INCLUDE=include
INCLUDE_LIB=libft/include_lib/
LIB_DIR=libft
LIB=libft/libft.a
SRC_DIR=src
HEADER=include/ls.h

all: lib $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -I $(INCLUDE) -I $(INCLUDE_LIB)
	@ printf "|---------------------------------|\n ✅ | $(WHITE)[$(GREEN)done$(WHITE)]$(COLOR_OFF) - ft_ls\n|---------------------------------|\n"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)
	@ printf "$(WHITE)[$(GREEN)created$(WHITE)]$(COLOR_OFF) - $@\n"

lib:
	@ make -C $(LIB_DIR)

clean:
	@make clean -C $(LIB_DIR)
	@rm -f $(OBJ) 
	@ printf "|---------------------------------|\n 🗑  | $(WHITE)[$(RED)remove$(WHITE)]$(COLOR_OFF) - objects of ft_ls\n|---------------------------------|\n"

fclean: clean
	@rm -f $(LIB)
	@rm -f $(NAME)
	@ printf "|---------------------------------|\n 🗑  | $(WHITE)[$(RED)remove$(WHITE)]$(COLOR_OFF) - $(LIB)\n|---------------------------------|\n"
	@ printf "|---------------------------------|\n 🗑  | $(WHITE)[$(RED)remove$(WHITE)]$(COLOR_OFF) - $(NAME)\n|---------------------------------|\n"

re: fclean all

.PHONY: all, clean, fclean, re
