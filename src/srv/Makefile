##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
## 
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
## 
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Wed Jun 17 22:08:47 2015 Emmanuel Chambon
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
			src/commands.c		\
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
