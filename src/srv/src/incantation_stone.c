/*
** incantation_stone.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sat Jul  4 22:04:32 2015 Hugo Prenat
*/

#include "zappy.h"

int	playerLevelUp(t_client *client, t_client *all)
{
  int	lvl;

  lvl = client->level;
  while (all)
    {
      if (all->pos[X] == client->pos[X] && all->pos[Y] == client->pos[Y] &&
	  all->level == lvl)
	all->level++;
      all = all->next;
    }
  return (1);
}

int	check_stones_hard(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 6 && tmp->content[2] > 0 && tmp->content[3] > 1 &&
      tmp->content[4] > 2 && tmp->content[6] > 0)
    {
      tmp->content[2]--;
      tmp->content[3] -= 2;
      tmp->content[4] -= 3;
      tmp->content[6]--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 7 && tmp->content[2] > 1 && tmp->content[3] > 1 &&
      tmp->content[4] > 1 && tmp->content[5] > 1 && tmp->content[6] > 1 &&
      tmp->content[7] > 0)
    {
      tmp->content[2] -= 2;
      tmp->content[3] -= 2;
      tmp->content[4] -= 2;
      tmp->content[5] -= 2;
      tmp->content[6] -= 2;
      tmp->content[7]--;
      return (playerLevelUp(client, all));
    }
  return (0);
}

int	check_stones_medium(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 4 && tmp->content[2] > 0 && tmp->content[3] > 0 &&
      tmp->content[4] > 1 && tmp->content[6] > 0)
    {
      tmp->content[2]--;
      tmp->content[3]--;
      tmp->content[4] -= 2;
      tmp->content[6]--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 5 && tmp->content[2] > 0 && tmp->content[3] > 1 &&
      tmp->content[4] > 0 && tmp->content[5] > 2)
    {
      tmp->content[2]--;
      tmp->content[3] -= 2;
      tmp->content[4]--;
      tmp->content[5] -= 3;
      return (playerLevelUp(client, all));
    }
  return (check_stones_hard(client, tmp, all));
}

int	check_stones(t_client *client, t_case *tmp, t_client *all)
{
  if (client->level == 1 && tmp->content[2] > 0)
    {
      tmp->content[2]--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 2 && tmp->content[2] > 0 && tmp->content[3] > 0 &&
      tmp->content[4] > 0)
    {
      tmp->content[2]--;
      tmp->content[3]--;
      tmp->content[4]--;
      return (playerLevelUp(client, all));
    }
  if (client->level == 3 && tmp->content[2] > 1 && tmp->content[4] > 0 &&
      tmp->content[6] > 1)
    {
      tmp->content[2] -= 2;
      tmp->content[4]--;
      tmp->content[6] -= 2;
      return (playerLevelUp(client, all));
    }
  return (check_stones_medium(client, tmp, all));
}

void		incantation_graphic(t_client *client, t_master *content,
				    char *players)
{
  t_client	*clients;

  if (!players && client->trigger[GRAPHIC])
    ssend(client->socket, "pie %lu %lu %d\n", client->pos[X], client->pos[Y],
	  0);
  else if (client->trigger[GRAPHIC])
    ssend(client->socket, "pie %lu %lu %d\n", client->pos[X], client->pos[Y],
	  check_stones(client, getCaseFromCoord
		       (client->pos[X], client->pos[Y], content->cases),
		       content->clients));
  clients = content->clients;
  while (clients && players)
    {
      if (client->id != clients->id && clients->pos[X] == client->pos[Y] &&
	  clients->pos[Y] == client->pos[Y] && (client->level - 1)
	  == clients->level)
	{
	  clients->level++;
	  if (client->trigger[GRAPHIC])
	    plv(transform_int(client->level), client, content);
	}
      clients = clients->next;
    }
}
