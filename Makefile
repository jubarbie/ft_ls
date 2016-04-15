# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2016/04/15 15:32:56 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-I Includes -Wall -Wextra -Werror
SRC=	Sources/main.c \
		Sources/param.c \
		Sources/ft_ls.c \
		Sources/error.c
OBJ=$(SRC:.c=.o)
LIBS=Libs/libft
NAME=ft_ls

$(NAME): $(OBJ)
	make -C $(LIBS)
	$(CC) -L$(LIBS) -lft -o $@ $^

all: $(NAME)
	
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
