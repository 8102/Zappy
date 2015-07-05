##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
##
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
##
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Sun Jul  5 02:55:34 2015 Emmanuel Chambon
##

CC		=	gcc -g

RM		=	rm -fr

NAME_CLIENT	=	zappy_ai

SRC_CLIENT	=	client.c			\
			init.c				\
			network.c			\
			utils.c				\

OBJ_DIR		=	obj/

SRC_DIR		=	src/

INC_DIR		=	include/

CFLAGS		=	-W -Wall -Wextra -I$(INC_DIR)

BUILD_PRINT	=	\e[1;34mBuilding\e[0m \e[1;33m$<\e[0m

OBJS		=	$(patsubst %.c,${OBJ_DIR}%.o, $(SRC_CLIENT))

FIRST		:=	$(shell test -d $(OBJ_DIR) || mkdir $(OBJ_DIR))

$(OBJ_DIR)%.o	:	$(patsubst %.c, ${SRC_DIR}%.c, %.c)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(NAME_CLIENT)	:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME_CLIENT)

all		:
			@$(MAKE) --no-print-directory $(NAME_CLIENT)

clean		:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean		:	clean
			$(RM) $(NAME_CLIENT)

re		:	fclean all

