/*
** fork.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 30 21:06:34 2015 Hugo Prenat
** Last update Tue Jun 30 23:55:20 2015 Hugo Prenat
*/

#include "zappy.h"

void		send_fork(t_master *content, int id)
{
  t_client	*cur;

  cur = content->clients;
  while (cur)
    {
      if (cur->trigger[GRAPHIC] == true)
	ssend(cur->socket, "pfk %d\n", id);
      cur = cur->next;
    }
}

void	_fork(char UNUSED*params,
	      t_client *client,
	      UNUSED t_master *content)
{
  ssend(client->socket, "ok\n");
  send_fork(content, client->id);
  add_egg(client->team, content, client->pos, client->id);
}
