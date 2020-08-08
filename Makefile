# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-corr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/07 14:17:11 by jle-corr          #+#    #+#              #
#    Updated: 2020/08/07 14:25:49 by jle-corr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LINUXPATH = ./linux
MACPATH = ./mac

all : mk_linux

mac : mk_mac

mk_linux :
	make -C $(LINUXPATH)

mk_mac :
	make -C $(MACPATH)


#CLEAN LINUX

clean :
	make clean -C $(LINUXPATH)

fclean : clean
	make fclean -C $(LINUXPATH)

re : fclean all


#CLEAN MAC

cleanmac :
	make clean -C $(MACPATH)

fcleanmac : cleanmac
	make fclean -C $(MACPATH)

remac : fcleanmac mac
