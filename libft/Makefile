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
CFLAGS=-Wall -Werror -Wextra
SRC=./src_lib/ft_memset.c \
	./src_lib/ft_atoi.c \
	./src_lib/ft_bzero.c \
	./src_lib/ft_count.c \
	./src_lib/ft_count_words.c \
	./src_lib/ft_isalnum.c \
	./src_lib/ft_isalpha.c \
	./src_lib/ft_isascii.c \
	./src_lib/ft_isdigit.c \
	./src_lib/ft_isprint.c \
	./src_lib/ft_itoa.c \
	./src_lib/ft_itoa_base.c \
	./src_lib/ft_lstadd.c \
	./src_lib/ft_lstdel.c \
	./src_lib/ft_lstdelone.c \
	./src_lib/ft_lstiter.c \
	./src_lib/ft_lstlen.c \
	./src_lib/ft_lstmap.c \
	./src_lib/ft_lstnew.c \
	./src_lib/ft_lstprint.c \
	./src_lib/ft_memalloc.c \
	./src_lib/ft_memccpy.c \
	./src_lib/ft_memchr.c \
	./src_lib/ft_memcmp.c \
	./src_lib/ft_memcpy.c \
	./src_lib/ft_memdel.c \
	./src_lib/ft_memmove.c \
	./src_lib/ft_memset.c \
	./src_lib/ft_putchar.c \
	./src_lib/ft_putchar_fd.c \
	./src_lib/ft_putendl.c \
	./src_lib/ft_putendl_fd.c \
	./src_lib/ft_putnbr.c \
	./src_lib/ft_putnbr_fd.c \
	./src_lib/ft_putstr.c \
	./src_lib/ft_putstr_fd.c \
	./src_lib/ft_sqrt.c \
	./src_lib/ft_stralldel.c \
	./src_lib/ft_strcat.c \
	./src_lib/ft_strchr.c \
	./src_lib/ft_strclr.c \
	./src_lib/ft_strcmp.c \
	./src_lib/ft_strcpy.c \
	./src_lib/ft_strdel.c \
	./src_lib/ft_strdup.c \
	./src_lib/ft_strequ.c \
	./src_lib/ft_striter.c \
	./src_lib/ft_striteri.c \
	./src_lib/ft_strjoin.c \
	./src_lib/ft_strlcat.c \
	./src_lib/ft_strlen.c \
	./src_lib/ft_strmap.c \
	./src_lib/ft_strmapi.c \
	./src_lib/ft_strncat.c \
	./src_lib/ft_strncmp.c \
	./src_lib/ft_strncpy.c \
	./src_lib/ft_strnequ.c \
	./src_lib/ft_strnew.c \
	./src_lib/ft_strnstr.c \
	./src_lib/ft_strrchr.c \
	./src_lib/ft_strsplit.c \
	./src_lib/ft_strstr.c \
	./src_lib/ft_strsub.c \
	./src_lib/ft_strtrim.c \
	./src_lib/ft_tolower.c \
	./src_lib/ft_toupper.c \
	./src_lib/get_next_line.c \
	./src_lib/check_percent.c \
	./src_lib/ft_printf.c \
	./src_lib/ft_putnbr_base.c \
	./src_lib/write_symbol_s_uni.c \
	./src_lib/write_to_buffer.c \
	./src_lib/write_type_c.c \
	./src_lib/write_type_s.c \
	./src_lib/write_type_d_i.c \
	./src_lib/write_type_x_p.c \
	./src_lib/write_type_o.c \
	./src_lib/write_type_u.c \
	./src_lib/write_colors.c
OBJ=$(SRC:.c=.o)
NAME=libft.a
INCLUDE=include_lib
SRC_DIR=src_lib
HEADER=include_lib/libft.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar rc $(NAME) $(OBJ)
	@ printf "|---------------------------------|\n ✅ | $(WHITE)[$(GREEN)done$(WHITE)]$(COLOR_OFF) - libft.a\n|---------------------------------|\n"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDE)
	@ printf "$(WHITE)[$(GREEN)created$(WHITE)]$(COLOR_OFF) - $@\n"

clean:
	@rm -f $(OBJ)
	@ printf "|---------------------------------|\n 🗑  | $(WHITE)[$(RED)remove$(WHITE)]$(COLOR_OFF) - objects of libft\n|---------------------------------|\n"

fclean: clean
	@rm -f $(NAME)
	@ printf "|---------------------------------|\n 🗑  | $(WHITE)[$(RED)remove$(WHITE)]$(COLOR_OFF) - $(NAME)\n|---------------------------------|\n"

re: fclean all

.PHONY: all, clean, fclean, re
