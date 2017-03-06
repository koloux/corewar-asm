#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/21 18:14:44 by lpousse           #+#    #+#              #
#    Updated: 2017/03/06 13:48:19 by lpousse          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

all: libft corewar asm

libft:
	make -C ./libft -j8

corewar:
	make -C ./corewar
	cp Corewar/corewar ./

asm:
	make -C ./asm
	cp Asm/asm ./

clean:
	make -C ./libft clean
	make -C ./corewar clean
	make -C ./asm clean

fclean:
	make -C ./libft fclean
	make -C ./corewar fclean
	make -C ./asm fclean
	rm corewar asm

re: fclean all

.PHONY: libft corewar asm clean fclean re