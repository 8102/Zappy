/*
** fork.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 30 21:06:34 2015 Hugo Prenat
** Last update Sat Jul  4 01:48:10 2015 Hugo Prenat
*/

#include "zappy.h"

void	_fork(char UNUSED*params,
	      t_client *client,
	      t_master *content)
{
  ssend(client->socket, "ok\n");
  ssend_graphics(content, "pfk %d\n", client->id);
  add_egg(client->team, content, client->pos, client->id);
}
