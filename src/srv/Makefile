##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
## 
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
## 
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Tue Jun 16 12:01:16 2015 Emmanuel Chambon
##

CC		=	gcc

RM		=	rm -f

INC		=	include

CFLAGS		=	-std=c99 -W -Wall -Wextra -I$(INC) -D_POSIX_C_SOURCE=200809L

NAME_SERVER	=	server

SRC_SERVER	=	src/main.c		\
			src/server.c		\
			src/server_init.c	\
			src/server_idle.c	\
			src/socketutils.c	\
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
