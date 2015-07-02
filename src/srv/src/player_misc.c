/*
** player_misc.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Thu Jul  2 15:37:37 2015 Hugo Prenat
** Last update Thu Jul  2 17:13:26 2015 Hugo Prenat
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

void		plv(char *params,
		    t_client UNUSED*client,
		    t_master *content)
{
  int		nbrP;
  t_client	*clients;

  if (!params || !params[0])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  nbrP = atoi(params);
  clients = content->clients;
  while (clients)
    {
      if (clients->id == nbrP)
	{
	  ssend(client->socket, "plv %d %d\n", nbrP, clients->level);
	  return ;
	}
      clients = clients->next;
    }
  ssend(client->socket, "sbp\n");
}

void		pin(char *params,
		    t_client *client,
		    t_master *content)
{
  int		nbrP;
  t_client	*clients;

  if (!params || !params[0])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  nbrP = atoi(params);
  clients = content->clients;
  while (clients)
    {
      if (clients->id == nbrP)
	{
	  ssend(client->socket, "pin %d %u %u %d %d %d %d %d %d\n",
		clients->id, clients->pos[0], clients->pos[1],
		clients->resources[MEAL], clients->resources[LINEMATE],
		clients->resources[DERAUMERE], clients->resources[SIBUR],
		clients->resources[MENDIANE], clients->resources[MENDIANE],
		clients->resources[PHIRAS], clients->resources[THYSTAME]);
	  return ;
	}
      clients = clients->next;
    }
  ssend(client->socket, "sbp\n");
}
