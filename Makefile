##
## Makefile for  in /home/chambo_e/epitech/PSU_2014_myirc
## 
## Made by Emmanuel Chambon
## chambo_e  <chambon.emmanuel@gmail.com>
## 
## Started on  Wed Apr  8 22:49:16 2015 Emmanuel Chambon
## Last update Tue Jun 16 09:21:18 2015 Emmanuel Chambon
##

EXE_CLIENT	:=	client

EXE_SERVER	:=	server

RM		:=	rm -f

SERVER		:=	src/srv

CLIENT		:=	src/cli

all		:
			make -C $(SERVER)
			@cp $(SERVER)/$(EXE_SERVER) .
			@echo '#! /bin/sh' > $(EXE_CLIENT)
			@echo 'npm start --prefix ./src/cli' >> $(EXE_CLIENT)
			@chmod 755 $(EXE_CLIENT)
			@npm install --prefix $(CLIENT)

clean		:
			make clean -C $(SERVER)

fclean		:	clean
			make fclean -C $(SERVER)
			$(RM) $(EXE_SERVER) $(EXE_CLIENT)

re		:	fclean all
