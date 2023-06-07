# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aen-naas <aen-naas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/13 18:13:02 by ilasrarf          #+#    #+#              #
#    Updated: 2023/06/04 22:13:39 by aen-naas         ###   ########.fr        #
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
	  lib/ft_write_error.c \
	  lib/ft_itoa.c \
	  lib/ft_strdup.c \
	  lib/ft_strlen.c \
	  lib/ft_memcpy.c \
	  lib/ft_calloc.c \
	  lib/ft_bzero.c \
	  lib/ft_memset.c \
	  lib/ft_strjoin.c \
	  lib/ft_split.c \
	  lib/ft_lst_new_prs.c \
	  lib/ft_lstadd_back_prs.c \
	  parsing/ft_parser.c \
	  lib/ft_lstdelone.c \
	  lib/ft_lstclear.c \
	  lib/ft_putstr_fd.c \
	  lib/ft_strcmp.c \
	  lib/ft_strncmp.c \
	  lib/ft_strchr.c \
	  lib/ft_free.c \
	  lib/ft_atoi.c \
	  parsing/prs_tools.c \
	  parsing/prs_tools1.c \
	  parsing/prs_tools2.c \
	  parsing/prs_tools3.c \
	  parsing/prs_tools4.c \
	  excution/main_exc.c \
	  excution/exc_tools.c \
	  excution/exc_tools1.c \
	  excution/exc_tools2.c \
	  excution/exit_status.c \
	  excution/fill_envlist.c \
	  builtins/builtins.c \
	  builtins/builtins1.c \
	  builtins/builtins2.c \
	  builtins/builtins3.c \
	  builtins/builtins4.c \
	  builtins/builtins5.c \
	  builtins/norm_builtins.c \
	  norm_main.c
	  

SRC_O =  ${SRC:.c=.o}

NAME = minishell
CC = cc -g 
FLAGS =  -Wall -Werror -Wextra
RM = rm -rf


all: ${NAME}

${NAME}: ${SRC_O}
	${CC}  ${SRC_O} -o ${NAME} -lreadline -L /Users/ilasrarf/.brew/opt/readline/lib -I/Users/ilasrarf/.brew/opt/readline/include

%.o: %.c minishell.h
	${CC} ${FLAGS} -c $< -o $@

clean:
	${RM} ${SRC_O}

fclean: clean
	${RM} ${NAME}

re: fclean all