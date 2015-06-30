##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
##
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
##
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Tue Jun 30 21:07:06 2015 Hugo Prenat
##

DEBUG		=	yes

CC		=	gcc

RM		=	rm -fr

NAME_SERVER	=	zappy_server

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
			graphic.c		\
			direction.c		\
			expulse.c		\
			pos.c			\
			misc.c			\
			voir.c			\
			voir_misc.c		\
			prend.c			\
			pose.c			\
			fork.c			\
			ppo.c			\
			broadcast.c		\
			broadcast_orient.c

OBJ_DIR		=	obj/

SRC_DIR		=	src/

INC_DIR		=	include/

CFLAGS		=	-W -Wall -Wextra -I$(INC_DIR) -lm

ifeq ($(DEBUG),yes)

CFLAGS 		+= 	-g3

else

CFLAGS		+= 	-O3

endif

BUILD_PRINT	=	\e[1;34mBuilding\e[0m \e[1;33m$<\e[0m

OBJS		=	$(patsubst %.c,${OBJ_DIR}%.o, $(SRC_SERVER))

FIRST		:=	$(shell test -d $(OBJ_DIR) || mkdir $(OBJ_DIR))

$(OBJ_DIR)%.o	:	$(patsubst %.c, ${SRC_DIR}%.c, %.c)
			@echo -e "$(BUILD_PRINT)" && $(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERVER)	:	$(OBJS)
			$(CC) $(OBJS) -o $(NAME_SERVER) -lm

all		:
			@$(MAKE) --no-print-directory $(NAME_SERVER)

clean		:
			$(RM) $(OBJS) $(OBJ_DIR)

fclean		:	clean
			$(RM) $(NAME_SERVER)

re		:	fclean all
