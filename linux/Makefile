# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/23 16:42:04 by jle-corr          #+#    #+#              #
#    Updated: 2020/08/07 14:29:43 by jle-corr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

#INCLUDE
INCLUDEPATH = includes
MLXPATH = minilibx-linux
LIBFTPATH = libft

INCLUDES = $(INCLUDEPATH)/*.h
INCLUDES += $(MLXPATH)/mlx.h
INCLUDES += $(LIBFTPATH)/libft.h
INC = $(addprefix -I , $(INCLUDEPATH)/ $(MLXPATH)/ $(LIBFTPATH)/)

#LIB
LIBFT = $(LIBFTPATH)/libft.a
LIBMLX = $(MLXPATH)/libmlx.a

#FLAG
FLAGS = -Wall -Wextra -Werror
MLXFLAG = -lmlx -lm -lbsd -lXext -lX11

#SRC & OBJ PATH
SRCPATH = ./src
PARSINGPATH = $(SRCPATH)/parsing
RENDERINGPATH = $(SRCPATH)/rendering
OBJPARSINGPATH = $(PARSINGPATH)/obj
OBJRENDERINGPATH = $(RENDERINGPATH)/obj


#SRCS
PARSING = $(addprefix $(PARSINGPATH)/, extract_cub_file.c handle_map.c \
		  verify_map.c)
RENDERING = $(addprefix $(RENDERINGPATH)/, ft_utils.c image_drawing.c \
			key_event.c main.c raycast.c raycast_utils.c \
			sprite_drawing.c record_sprite.c save_bmp.c)

#OBJS
OBJ = $(PARSING:$(PARSINGPATH)/%.c=$(OBJPARSINGPATH)/%.o)
OBJ += $(RENDERING:$(RENDERINGPATH)/%.c=$(OBJRENDERINGPATH)/%.o)



all : make_objdir mk_libft mk_mlx $(NAME)



make_objdir:
	@if [ ! -d $(OBJPARSINGPATH) ]; then mkdir $(OBJPARSINGPATH); fi
	@if [ ! -d $(OBJRENDERINGPATH) ]; then mkdir $(OBJRENDERINGPATH); fi

mk_libft :
	@echo "\nChecking libft"
	@make -C $(LIBFTPATH)

mk_mlx :
	@echo "\nChecking mlx"
	@make -C $(MLXPATH)



$(NAME) : message $(OBJ) $(INCLUDEPATH)/cub3d.h
	@echo "\nMaking $(NAME)"
	clang -o $@ $(INC) $(OBJ) $(LIBFT) -L $(MLXPATH) $(MLXFLAG)
	@echo "\n$(NAME) is built"

message :
	@echo "\nMaking objetcs"



$(OBJPARSINGPATH)/%.o : $(PARSINGPATH)/%.c $(INCLUDES)
	clang $(FLAGS) $(INC) -c $< -o $@

$(OBJRENDERINGPATH)/%.o : $(RENDERINGPATH)/%.c $(INCLUDES)
	clang $(FLAGS) $(INC) -c $< -o $@



#CLEAN
.PHONY : clean fclean re

clean :
	@echo "\nremoving $(NAME) objects"
	rm -rf $(OBJ)
	@echo "cleaning libft objects"
	@make clean -C $(LIBFTPATH)
	@echo "cleaning MLX"
	@make clean -C $(MLXPATH)

fclean : clean
	@echo "\nremoving $(NAME)"
	@rm -f $(NAME)
	@echo "\nremoving libft.a"
	@make fclean -C $(LIBFTPATH)
	@echo "\nremoving libmlx.a"
	@rm -f $(LIBMLX)

re : fclean all
