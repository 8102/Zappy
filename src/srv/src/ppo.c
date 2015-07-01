/*
** ppo.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 30 20:50:18 2015 Hugo Prenat
** Last update Tue Jun 30 20:50:39 2015 Hugo Prenat
*/

#include "zappy.h"

void		ppo(char *params,
		    t_client *client,
		    t_master *content)
{
  int		id;
  t_client	*tmp;

  if (!params)
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  id = atoi(params);
  tmp = content->clients;
  while (tmp)
    {
      if (tmp->id == id)
	break ;
      tmp = tmp->next;
    }
  if (!tmp || tmp->id != id)
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  ssend(client->socket, "ppo %d %d %d %d\n", tmp->id,
	tmp->pos[X], tmp->pos[Y], tmp->orient);
}
