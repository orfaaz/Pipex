# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agamay <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/16 11:28:00 by agamay            #+#    #+#              #
#    Updated: 2024/12/02 17:11:32 by agamay           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c \
	pipex_parser.c \
	pipex_lstfct.c \
	pipex_utils.c

LIBDIR = ../libft
LIB = $(LIBDIR)/libft.a

OBJDIR = .obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -I $(LIBDIR)/

CC = cc

$(NAME): $(LIB) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB) $(LDFLAGS)

all: $(LIB) $(OBJ) $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $^ $(LDFLAGS)

$(LIB):
	make -sC $(LIBDIR)

clean:
	rm -rf $(OBJDIR)
	make -sC $(LIBDIR) clean

fclean: clean
	rm -f $(NAME)
	make -sC $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
