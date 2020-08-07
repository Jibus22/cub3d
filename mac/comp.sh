#!/bin/bash

COMP='clang -Wall -Wextra -Werror'
SAN='-g3 -fsanitize=address -fno-omit-frame-pointer'
LIBFTPATH='./libft/'
LIBFT='./libft/libft.a'
INCLUDEPATH='./includes'
MLXPATH='./minilibx_mms_20200219'
MLXINC=$MLXPATH
MLXLIB=$MLXPATH
MLXFLAG='-L '$MLXPATH' -lmlx -framework AppKit libmlx.dylib'
ALL_C_FILES='./src/rendering/*.c ./src/parsing/*.c'

if [ "$2" = "san" ]; then
	$COMP $SAN -I  $MLXINC -I $LIBFTPATH -I $INCLUDEPATH $ALL_C_FILES $LIBFT -L $MLXLIB $MLXFLAG;
else
	$COMP -I $MLXINC -I $LIBFTPATH -I $INCLUDEPATH $ALL_C_FILES $LIBFT $MLXFLAG;
fi;

if [ "$2" = "san" ]; then
	./a.out $1;
else
	./a.out $*;
fi
