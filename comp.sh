COMP='gcc -Wall -Wextra -Werror'
SAN='-g3 -fsanitize=address -fno-omit-frame-pointer'
LIBFTPATH='./libft/'
LIBFT='./libft/libft.a'
MLXPATH='/usr/local/'
MLXINC=$MLXPATH'include'
MLXLIB=$MLXPATH'lib'
MLXFLAG='-lmlx -framework OpenGL -framework AppKit'

if [ "$2" = "san" ]; then
	$COMP $SAN -I  $MLXINC -I $LIBFTPATH *.c $LIBFT -L $MLXLIB $MLXFLAG;
else
	$COMP -I $MLXINC -I $LIBFTPATH *.c $LIBFT -L $MLXLIB $MLXFLAG;
fi;

if [ "$2" = "san" ]; then
	./a.out $1;
else
	./a.out $*;
fi
