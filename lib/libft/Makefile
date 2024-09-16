# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/28 08:06:16 by decerrit          #+#    #+#              #
#    Updated: 2024/07/27 16:41:44 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
PACK = ar rcs
OBJ_DIRS = obj/
CFLAGS = -Wall -Wextra -Werror -g
FRM = rm -rf
CORE_FILES = \
	ft_memset.c		\
	ft_bzero.c		\
	ft_memcpy.c		\
	ft_memmove.c	\
	ft_memchr.c		\
	ft_memcmp.c		\
	ft_strlen.c		\
	ft_isalpha.c	\
	ft_isdigit.c	\
	ft_isalnum.c	\
	ft_isascii.c	\
	ft_isprint.c	\
	ft_toupper.c	\
	ft_tolower.c	\
	ft_strchr.c		\
	ft_strrchr.c	\
	ft_strncmp.c	\
	ft_strdup.c		\
	ft_strnstr.c	\
	ft_atoi.c		\
	ft_calloc.c		\
	ft_strlcpy.c	\
	ft_strlcat.c	\
	ft_strcmp.c	\
	get_next_line.c	\
	get_next_line_utils.c	\
	ft_print_error.c		\

UTILS_FILES = \
	ft_itoa.c		\
	ft_putchar_fd.c	\
	ft_putendl_fd.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_split.c		\
	ft_striteri.c	\
	ft_strjoin.c	\
	ft_strmapi.c	\
	ft_strtrim.c	\
	ft_substr.c		\

BONUS_FILES = \
	ft_lstnew_bonus.c\
	ft_lstadd_front_bonus.c\
	ft_lstsize_bonus.c\
	ft_lstlast_bonus.c\
	ft_lstadd_back_bonus.c\
	ft_lstdelone_bonus.c\
	ft_lstclear_bonus.c\
	ft_lstiter_bonus.c\
	ft_lstmap_bonus.c\
	

CORE_OBJS = $(patsubst %.c, $(OBJ_DIRS)%.o, $(CORE_FILES))
UTILS_OBJS = $(patsubst %.c, $(OBJ_DIRS)/%.o, $(UTILS_FILES))
BONUS_OBJS = $(patsubst %.c, $(OBJ_DIRS)%.o, $(BONUS_FILES))
OBJS_CORE_UTILS = $(CORE_OBJS) $(UTILS_OBJS)
#Genero archivos que digan que se ejecuto los default y/o bonus
DEFAULT_PART = .default
BONUS_PART = .bonus
obj/%.o: %.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIRS):
	mkdir -p obj/
		
$(NAME): $(DEFAULT_PART)
$(DEFAULT_PART): $(OBJS_CORE_UTILS)
	$(PACK) $(NAME) $(OBJS_CORE_UTILS)
	@touch $(DEFAULT_PART)
$(BONUS_PART): $(BONUS_OBJS)
	$(PACK) $(NAME) $(BONUS_OBJS)
	@touch $(BONUS_PART)
all: $(DEFAULT_PART)
bonus: $(BONUS_PART)
#Limpio los archivos .c del bonus y obligatorios y los.bonus y .default
clean:
	$(FRM) $(OBJS_CORE_UTILS) $(BONUS_OBJS)
	$(FRM) $(DEFAULT_PART) $(BONUS_PART)
fclean: clean
	$(FRM) $(NAME)
debug: 
	$(CC) $(CFLAG)
re: fclean all
.PHONY: re clean fclean bonus all