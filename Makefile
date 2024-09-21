# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 12:20:24 by adherrer          #+#    #+#              #
#    Updated: 2024/09/20 23:16:48 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Werror -Wall -Wextra  -g3 #-fsanitize=thread 

RM = rm -rf
OBJ_DIRS = obj/
SRCS = 	 lib/ft_sarrprint.c \
src/excep/service_excep.c\
lib/ft_sarrsize.c lib/ft_chrpos.c \
lib/ft_sarradd.c \
lib/get_token.c \
lib/ft_getenv.c \
lib/ft_isbuiltin.c \
lib/ft_sarrfree.c \
lib/ft_idbystr.c \
lib/ft_idbychar.c \
lib/ft_find_str.c \
lib/ft_get_path.c \
lib/ft_delete_cmd.c \
lib/ft_realloc.c \
lib/ft_strdelchr.c \
lib/ft_sarrdel.c \
lib/ft_add_exec.c \
lib/ft_add_cmd.c \
lib/ft_duparr.c \
lib/ft_clean_quote.c \
lib/ft_keep_content_byquote.c \
lib/ft_keep_content_byspace.c \
lib/ft_handler_keep_content.c \
lib/ft_count_blocks.c \
src/minishell.c \
src/fsm/parser.c \
src/fsm/config.c \
src/fsm/execute.c \
src/fsm/clear.c \
src/fsm/subprocess.c \
src/resource/init_learning.c \
src/resource/config_learning.c \
src/resource/exec_learning.c \
src/config/ft_conf_and.c \
src/config/ft_conf_pipe.c \
src/config/ft_conf_or.c \
src/config/ft_conf_less.c \
src/config/ft_conf_heredoc.c \
src/config/ft_conf_greater.c \
src/config/ft_conf_append.c \
src/config/ft_conf_amper.c \
src/config/ft_conf_cmd.c \
src/exec/builtins/ft_exec_echo.c \
src/exec/builtins/ft_exec_cd.c \
src/exec/builtins/ft_exec_pwd.c \
src/exec/builtins/ft_exec_export.c \
src/exec/builtins/ft_exec_unset.c \
src/exec/builtins/ft_exec_env.c \
src/exec/builtins/ft_exec_exit.c \
src/exec/dispatch_command.c\
src/exec/ft_exec_cmd.c\
src/exec/ft_exec_greater.c\
src/exec/ft_exec_amper.c\
src/exec/ft_exec_append.c\
src/exec/ft_exec_less.c\
src/exec/do_exec.c\
src/exec/ft_exec_heredoc.c\
src/exec/ft_exec_pipe.c
		

LIBFT = lib/libft/libft.a
OBJ = $(patsubst %.c, $(OBJ_DIRS)%.o, $(SRCS))

obj/%.o: %.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@


CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(NAME) : $(OBJ)
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS)  $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"


$(OBJ_DIRS):
	mkdir -p obj/lib 
	mkdir -p obj/src 
	mkdir -p obj/src/excep
	mkdir -p obj/src/resource 
	mkdir -p obj/src/exec 
	mkdir -p obj/src/exec/builtins 
	mkdir -p obj/src/fsm
	mkdir -p obj/src/config

all :$(OBJ_DIR) $(NAME)

fclean : clean
	$(RM) $(NAME)
	make clean -C lib/libft
	make fclean -C lib/libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIRS)
	make clean -C lib/libft

re : fclean all


.PHONY:     all clean fclean re