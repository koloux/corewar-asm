# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 12:50:44 by lpousse           #+#    #+#              #
#    Updated: 2017/03/06 13:58:01 by lpousse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
SRC_NAME = corewar.c parsing.c tools.c tools2.c init.c processes.c battle.c get_params.c instructs1.c instructs2.c instructs3.c instructs4.c op.c
SRC_PATH = ./
OBJ_PATH = obj/
INC_PATH = ./ ../libft/includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -L ../libft
LDLIBS = -lft

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INCS = op.h ../libft/includes/libft.h

all: mklib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INCS)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	rm -fv $(NAME)

re: fclean all

.PHONY: all clean fclean re mklib norme
