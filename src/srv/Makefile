##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
## 
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
## 
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Thu Jun 18 17:24:38 2015 Emmanuel Chambon
##

CC		=	gcc -g

RM		=	rm -f

INC		=	include

CFLAGS		=	-W -Wall -Wextra -I$(INC)

NAME_SERVER	=	server

SRC_SERVER	=	src/main.c		\
			src/zappy.c		\
			src/init.c		\
			src/server.c		\
			src/client.c		\
			src/client_handler.c	\
			src/commands.c		\
			src/auth.c		\
			src/server_init.c	\
			src/server_idle.c	\
			src/socketutils.c	\
			src/rbinit.c		\
			src/misc.c		

OBJS		=	$(SRC_SERVER:.c=.o)

all		:
			@$(MAKE) --no-print-directory $(NAME_SERVER)

server		:	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME_SERVER)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME_SERVER) $(NAME_CLIENT)

re		:	fclean all
