##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
##
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
##
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Wed Jun 17 02:30:51 2015 Jean-Baptiste Grégoire
##

EXE_CLIENT	:=	client

EXE_SERVER	:=	server

RM		:=	rm -f

SERVER		:=	src/srv

CLIENT		:=	src/cli

all		:
			make -C $(SERVER)
			@cp $(SERVER)/$(EXE_SERVER) .
			@cp save $(EXE_CLIENT) # i'm crook !
			@chmod 755 $(EXE_CLIENT)
			@npm install --prefix $(CLIENT)

clean		:
			make clean -C $(SERVER)

fclean		:	clean
			make fclean -C $(SERVER)
			$(RM) $(EXE_SERVER) $(EXE_CLIENT)

re		:	fclean all
