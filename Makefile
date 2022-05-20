# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbounor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 12:57:14 by lbounor           #+#    #+#              #
#    Updated: 2022/05/20 12:57:16 by lbounor          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER		=	includes/minitalk.h
LIBFT		=	libft/*.c
OBJS		= 	sources/server.o sources/client.o

CFLAGS = -Wall -Wextra -Werror
CC = gcc
RM = rm -rf

all : server client

server: ${HEADER} ${OBJS}
	$(CC) $(CFLAGS) sources/server.c ${LIBFT}  -o server
	@echo "\033[92m\n[\\\\\\\ SERVER OK ///////]\n\033[0m"
client: ${HEADER} ${OBJS}
	$(CC) $(CFLAGS) sources/client.c ${LIBFT} -o client
	@echo "\033[92m\n[\\\\\\\ CLIENT OK ///////]\n\033[0m"

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) server
	$(RM) client
	$(RM) sources/*.o
	@echo "\033[91m\n[\\\\\\\ ALL CLEAN ///////]\n\033[0m"

fclean : clean

re : fclean all

.PHONY : all clean bonus fclean re