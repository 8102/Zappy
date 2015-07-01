##
## Makefile for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
##
## Made by TommyStarK
## Login   <milox_t@epitech.eu>
##
## Started on  Sat Jun 27 23:15:04 2015 TommyStarK
## Last update Tue Jun 30 23:45:28 2015 Milox Thomas
##

NAME 	=	zappy_client_c

SRC 	= 	client.c				\
		network.c				\
		init.c					\
		utils.c

OBJ	=	$(SRC:.c=.o)


name:		$(OBJ)
		gcc -W -Wall -Wextra -Werror $(SRC) -o $(NAME) -g


clean:
		rm -rf $(OBJ)
