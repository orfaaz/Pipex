# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agamay <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 11:28:00 by agamay            #+#    #+#              #
#    Updated: 2024/11/16 11:28:03 by agamay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
	pipex_parser.c \
	pipex_lstfct.c

SRC_TEST = test01.c

LIB = libft.a

OBJ = $(SRC:.c=.o)

OBJ_TEST = $(SRC_TEST:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

$(NAME): libft $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

test: libft $(OBJ_TEST)
	$(CC) -o $@ $(OBJ_TEST) $(LIB)

libft:
	make -C ../libft
	cp ../libft/libft.a ./
	make fclean -C ../libft

all: $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_TEST)

fclean: clean
	rm -f $(NAME)
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re test libft