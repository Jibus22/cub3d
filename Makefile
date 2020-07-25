# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/23 16:42:04 by jle-corr          #+#    #+#              #
#    Updated: 2020/07/25 20:20:29 by jle-corr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#COLORS
BLUE = \033[1;34m
GREY = \033[8;90m
YELLOW = \033[1;33m
YELLO = \033[8;93m
END = \033[0m

#INCLUDE
INCLUDEPATH = /Users/lecorre/42/cub3d/includes
MLXPATH = /usr/local/
MLXINC = $(MLXPATH)include
LIBFTPATH = libft

#LIB
LIBFT = $(LIBFTPATH)/libft.a
MLXLIB = $(MLXPATH)lib

#FLAG
FLAGS = -Wall -Wextra -Werror
MLXFLAG = -lmlx -framework OpenGL -framework AppKit

#SRC & OBJ PATH
SRCPATH = ./src
PARSINGPATH = $(SRCPATH)/parsing
RENDERINGPATH = $(SRCPATH)/rendering
OBJPARSINGPATH = $(PARSINGPATH)/obj
OBJRENDERINGPATH = $(RENDERINGPATH)/obj


#SRCS
PARSING = $(addprefix $(PARSINGPATH)/, extract_cub_file.c handle_map.c \
		  verify_map.c)
RENDERING = $(addprefix $(RENDERINGPATH)/, ft_error.c ft_pixel_put.c \
			image_drawing.c key_event.c main.c raycast.c raycast_utils.c \
			sprite_drawing.c record_sprite.c)

#OBJS
OBJ = $(PARSING:$(PARSINGPATH)/%.c=$(OBJPARSINGPATH)/%.o)
OBJ += $(RENDERING:$(RENDERINGPATH)/%.c=$(OBJRENDERINGPATH)/%.o)



all : make_obj_dir libft_all $(NAME)



make_obj_dir:
	@if [ ! -d $(OBJPARSINGPATH) ]; then mkdir $(OBJPARSINGPATH); fi
	@if [ ! -d $(OBJRENDERINGPATH) ]; then mkdir $(OBJRENDERINGPATH); fi

libft_all :
	@echo "\n$(END)$(BLUE)Checking libft$(END)$(GREY)"
	@make -C $(LIBFTPATH)



$(NAME) : message $(OBJ) $(INCLUDEPATH)/cub3d.h
	@echo "\n$(END)$(BLUE)Making $(NAME)$(END)$(GREY)"
	clang -o $@ $(OBJ) $(LIBFT) -L $(MLXLIB) $(MLXFLAG)
	@echo "\n$(END)$(BLUE)$(NAME) is built$(END)"

message :
	@echo "\n$(END)$(BLUE)Making objetcs$(END)$(GREY)"



$(OBJPARSINGPATH)/%.o : $(PARSINGPATH)/%.c
	clang $(FLAGS) -I $(MLXINC) -I $(LIBFTPATH) -I $(INCLUDEPATH) -c $< -o $@

$(OBJRENDERINGPATH)/%.o : $(RENDERINGPATH)/%.c
	clang $(FLAGS) -I $(MLXINC) -I $(LIBFTPATH) -I $(INCLUDEPATH) -c $< -o $@



#CLEAN
.PHONY : clean fclean re

clean :
	@echo "$(END)$(YELLOW)\nremoving $(NAME) objects$(END)$(YELLO)"
	rm -rf $(OBJ)
	@echo "$(END)$(YELLOW)cleaning libft objects$(END)"
	@make clean -C $(LIBFTPATH)

fclean : clean
	@echo "$(END)$(YELLOW)\nremoving $(NAME)$(END)$(YELLO)"
	rm -f $(NAME)
	@echo "$(END)$(YELLOW)\nremoving libft.a$(END)"
	@make fclean -C $(LIBFTPATH)

re : fclean all
