##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
## 
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
## 
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Tue Jun 23 19:18:48 2015 Hugo Prenat
##

CC		=	gcc -g

RM		=	rm -fr

NAME_SERVER	=	server

SRC_SERVER	=	main.c			\
			zappy.c			\
			init.c			\
			server.c		\
			client.c		\
			client_handler.c	\
			commands.c		\
			auth.c			\
			server_init.c		\
			server_idle.c		\
			socketutils.c		\
			cbinit.c		\
			rbinit.c		\
			rbutils.c		\
			case.c			\
			epur_str.c		\
			client_init.c		\
			egg.c			\
			misc.c

OBJ_DIR		=	obj/

SRC_DIR		=	src/

INC_DIR		=	include/

CFLAGS		=	-W -Wall -Wextra -I$(INC_DIR)

OBJS		=	$(patsubst %.c,${OBJ_DIR}%.o, $(SRC_SERVER))

FIRST		:=	$(shell test -d $(OBJ_DIR) || mkdir $(OBJ_DIR))

$(OBJ_DIR)%.o	:	$(patsubst %.c, ${SRC_DIR}%.c, %.c)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER)	:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME_SERVER)

all		:	$(NAME_SERVER)
##			@$(MAKE) --no-print-directory $(NAME_SERVER)

clean		:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean		:	clean
			$(RM) $(NAME_SERVER)

re		:	fclean all
