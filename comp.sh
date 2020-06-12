#!/bin/bash

COMP='clang -Wall -Wextra -Werror'
SAN='-g3 -fsanitize=address -fno-omit-frame-pointer'
LIBFTPATH='./libft/'
LIBFT='./libft/libft.a'
INCLUDEPATH='/Users/lecorre/42/cub3d/includes'
MLXPATH='/usr/local/'
MLXINC=$MLXPATH'include'
MLXLIB=$MLXPATH'lib'
MLXFLAG='-lmlx -framework OpenGL -framework AppKit'
ALL_C_FILES='./*.c ./parsing/*.c'

if [ "$2" = "san" ]; then
	$COMP $SAN -I  $MLXINC -I $LIBFTPATH -I $INCLUDEPATH $ALL_C_FILES $LIBFT -L $MLXLIB $MLXFLAG;
else
	$COMP -I $MLXINC -I $LIBFTPATH -I $INCLUDEPATH $ALL_C_FILES $LIBFT -L $MLXLIB $MLXFLAG;
fi;

if [ "$2" = "san" ]; then
	./a.out $1;
else
	./a.out $*;
fi
