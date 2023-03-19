# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 18:13:02 by ilasrarf          #+#    #+#              #
#    Updated: 2023/03/19 18:16:41 by ilasrarf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c \
	  tools/ft_lexeing.c \
	  tools/handel_lex.c\
	  lib/ft_isalnum.c \
	  lib/ft_isalpha.c \
	  lib/ft_isdigit.c \
	  lib/ft_substr.c \
	  lib/ft_lstnew.c \
	  lib/ft_lstadd_back.c \
	  lib/ft_strdup.c \
	  lib/ft_strlen.c \
	  lib/ft_memcpy.c \
	  lib/ft_calloc.c \
	  lib/ft_bzero.c \
	  lib/ft_memset.c \
	  lib/ft_strjoin.c\
	  parsing/ft_parser.c \
	  

SRC_O =  ${SRC:.c=.o}

NAME = minishell
CC = cc
FLAGS = -Wall -Werror -Wextra
RM = rm -rf

all: ${NAME}

${NAME}: ${SRC_O}
	${CC} ${SRC_O} -o ${NAME} -lreadline

%.o: %.c minishell.h
	${CC} ${FLAGS} -c $< -o $@

clean:
	${RM} ${SRC_O}

fclean: clean
	${RM} ${NAME}

re: fclean all