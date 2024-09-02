# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 12:20:24 by adherrer          #+#    #+#              #
#    Updated: 2024/08/19 18:07:56 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g3  #-fsanitize=thread 

RM = rm -rf

SRCS = 	 lib/ft_sarrprint.c \
lib/ft_sarrsize.c lib/ft_chrpos.c \
lib/ft_sarradd.c \
lib/ft_sarrfree.c \
src/minishell.c \
src/resource/parser.c \
src/resource/init_learning.c \
src/fsm/ft_conf_and.c \
src/fsm/ft_conf_pipe.c \
src/fsm/ft_conf_or.c \
src/fsm/ft_conf_less.c \
src/fsm/ft_conf_heredoc.c \
src/fsm/ft_conf_greater.c \
src/fsm/ft_conf_append.c \
src/fsm/ft_conf_amper.c \
src/fsm/ft_conf_cmd.c \
src/exec/ft_exec_and.c \
src/exec/ft_exec_or.c\
src/exec/ft_exec_cmd.c\
src/exec/ft_exec_greater.c\
src/exec/do_exec.c\
src/exec/ft_exec_heredoc.c
		

LIBFT = lib/libft/libft.a
OBJ =  $(SRCS:.c=.o) 


CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(NAME) : $(OBJ)
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS)  $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make clean -C lib/libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(NAME)
	$(RM) $(OBJ)
	make clean -C lib/libft

re : fclean all


.PHONY:     all clean fclean re