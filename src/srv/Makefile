##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
##
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
##
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Sat Jul  4 05:19:25 2015 Emmanuel Chambon
##

DEBUG		=	yes

CC		=	gcc

RM		=	rm -fr

NAME_SERVER	=	zappy_server

SRC_SERVER	=	main.c			\
			params.c		\
			zappy.c			\
			zappy_init.c		\
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
			map_misc.c		\
			player_misc.c		\
			time.c			\
			broadcast.c		\
			broadcast_orient.c	\
			incantation.c		\
			creation.c		\
			timespec_lib.c		\
			timespec_utils.c	\
			timespec_add.c		\
			timespec_sub.c		\
			timespec_cmp.c		\
			win.c			\
			incantation_stone.c

OBJ_DIR		=	obj/

SRC_DIR		=	src/

INC_DIR		=	include/

CFLAGS		=	-std=c11 -W -Wall -Wextra -I$(INC_DIR) -lm -D_DEFAULT_SOURCE

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
