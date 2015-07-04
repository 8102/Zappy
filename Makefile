##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
##
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
##
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Sat Jul  4 01:51:24 2015 Emmanuel Chambon
##

EXE_CLIENT	:=	zappy_ai

EXE_CLIENT_BN	:=	zappy_ai_node

EXE_SERVER	:=	zappy_server

RM		:=	rm -f

SERVER		:=	src/srv

CLIENT_BN	:=	src/cli

CLIENT		:=	src/client_c


all		:
			@$(MAKE) --no-print-directory $(EXE_SERVER)
			@$(MAKE) --no-print-directory $(EXE_CLIENT)

zappy_server	:
			make -C $(SERVER)
			@cp $(SERVER)/$(EXE_SERVER) .

zappy_ai	:
			make -C $(CLIENT)
			@cp $(CLIENT)/$(EXE_CLIENT) .

zappy_ai_node	:
			@cp .save $(EXE_CLIENT_BN)
			@chmod 755 $(EXE_CLIENT_BN)
			@npm install --prefix $(CLIENT_BN)

clean		:
			@make clean -C $(SERVER)
			@make clean -C $(CLIENT)

fclean		:	clean
			@make fclean -C $(SERVER)
			@make fclean -C $(CLIENT)
			$(RM) $(EXE_SERVER) $(EXE_CLIENT) $(EXE_CLIENT_BN)

re		:	fclean all
