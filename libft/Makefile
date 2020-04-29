# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/11 04:58:03 by jle-corr          #+#    #+#              #
#    Updated: 2020/04/23 14:29:20 by jle-corr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEPS = libft.h
OBJDIR = libftobj

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
		ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
		ft_tolower.c ft_toupper.c ft_pow.c ft_putstr.c ft_strdel.c ft_strnew.c \
		ft_utoa.c ft_ltoa.c ft_ultoa.c ft_utox.c ft_utobx.c ft_ultox.c \
		ft_strncpy.c get_next_line.c join_newstr.c ft_freetab.c\
		
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
NAME = libft.a

all : $(NAME)

$(OBJDIR)/%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "\n\033[1;36mlibft objects are just built.\033[0m"
	@ar rcs $@ $(OBJ)
	@echo "\033[1;36m$@ is built !\033[0m"

.PHONY : clean
clean :
	@rm -rf $(OBJ)
	@echo "\n\033[1;33mlibft objects removed.\033[0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\033[1;33m$(NAME) removed.\033[0m"

re : fclean all
