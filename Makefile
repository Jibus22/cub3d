# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/23 16:42:04 by jle-corr          #+#    #+#              #
#    Updated: 2020/07/27 19:51:15 by jle-corr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#COLORS
BLUE = \033[1;34m
GREY = \033[8;90m
GREEN = \033[1;36m
RED = \033[1;31m
END = \033[0m

#INCLUDE
INCLUDEPATH = ./includes
MLXPATH = minilibx_mms_20200219
LIBFTPATH = libft

#LIB
LIBFT = $(LIBFTPATH)/libft.a

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



all : make_objdir mk_libft mk_mlx $(NAME)



make_objdir:
	@if [ ! -d $(OBJPARSINGPATH) ]; then mkdir $(OBJPARSINGPATH); fi
	@if [ ! -d $(OBJRENDERINGPATH) ]; then mkdir $(OBJRENDERINGPATH); fi

mk_libft :
	@echo "\n$(END)$(BLUE)Checking libft$(END)$(GREY)"
	@make -C $(LIBFTPATH)

mk_mlx :
	@echo "\n$(END)$(BLUE)Checking mlx$(END)$(GREY)"
	@make -C $(MLXPATH)



$(NAME) : message $(OBJ) $(INCLUDEPATH)/cub3d.h
	cp ./minilibx_mms_20200219/libmlx.dylib .
	@echo "\n$(END)$(BLUE)Making $(NAME)$(END)$(GREY)"
	clang -o $@ $(OBJ) $(LIBFT) $(MLXFLAG)
	@echo "\n$(END)$(GREEN)$(NAME) is built$(END)"

message :
	@echo "\n$(END)$(BLUE)Making objetcs$(END)$(GREY)"



$(OBJPARSINGPATH)/%.o : $(PARSINGPATH)/%.c
	clang $(FLAGS) -I $(MLXPATH) -I $(LIBFTPATH) -I $(INCLUDEPATH) -c $< -o $@

$(OBJRENDERINGPATH)/%.o : $(RENDERINGPATH)/%.c
	clang $(FLAGS) -I $(MLXPATH) -I $(LIBFTPATH) -I $(INCLUDEPATH) -c $< -o $@



#CLEAN
.PHONY : clean fclean re

clean :
	@echo "$(END)$(RED)\nremoving $(NAME) objects$(END)$(GREY)"
	rm -rf $(OBJ)
	@echo "$(END)$(RED)cleaning libft objects$(END)"
	@make clean -C $(LIBFTPATH)
	@echo "$(END)$(RED)cleaning MLX$(END)"
	@make clean -C $(MLXPATH)

fclean : clean
	@echo "$(END)$(RED)\nremoving $(NAME)$(END)$(GREY)"
	rm -f $(NAME)
	@echo "$(END)$(RED)\nremoving libft.a$(END)"
	@make fclean -C $(LIBFTPATH)

re : fclean all
