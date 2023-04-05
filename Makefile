# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilasrarf <ilasrarf@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 18:13:02 by ilasrarf          #+#    #+#              #
#    Updated: 2023/04/03 20:48:22 by ilasrarf         ###   ########.fr        #
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
	  lib/ft_itoa.c \
	  lib/ft_strdup.c \
	  lib/ft_strlen.c \
	  lib/ft_memcpy.c \
	  lib/ft_calloc.c \
	  lib/ft_bzero.c \
	  lib/ft_memset.c \
	  lib/ft_strjoin.c \
	  lib/ft_lst_new_prs.c \
	  lib/ft_lstadd_back_prs.c \
	  parsing/ft_parser.c \
	  lib/ft_lstdelone.c \
	  lib/ft_lstclear.c \
	  lib/ft_putstr_fd.c \
	  lib/ft_strcmp.c \
	  lib/ft_strncmp.c \
	  lib/ft_strchr.c \
	  parsing/prs_tools.c \
	  parsing/prs_tools1.c \
	  builtins/builtins.c \
	  builtins/builtins2.c

SRC_O =  ${SRC:.c=.o}

NAME = minishell
CC = cc -g 
FLAGS = -Wall -Werror -Wextra -g
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