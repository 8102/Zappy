/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sun Jul  5 03:45:22 2015 Hugo Prenat
*/

#include "zappy.h"

char		*check_string(char *str, t_client *client, int nbC)
{
  if (client->level == 1)
    return (nbC >= 1 ? str : NULL);
  if (client->level <= 3)
    return (nbC >= 2 ? str : NULL);
  if (client->level <= 5)
    return (nbC >= 4 ? str : NULL);
  return (nbC >= 6 ? str : NULL);
}

char		*check_level(t_client *client, t_client *clients)
{
  int		nbC;
  char		*str;
  char		*nbr;

  nbC = 1;
  if (!(str = malloc(2)))
    return (NULL);
  str[0] = 0;
  while (clients)
    {
      if (client->id != clients->id && clients->pos[X] == client->pos[X] &&
	  clients->pos[Y] == client->pos[Y] && client->level == clients->level)
	{
	  if (!(nbr = transform_int(clients->id)))
	    return (NULL);
	  str = realloc(str, strlen(str) + strlen(nbr) + 5);
	  strcat(str, nbr);
	  strcat(str, " ");
	  free(nbr);
	  nbC++;
	}
      clients = clients->next;
    }
  str[(strlen(str) > 0) ? strlen(str) - 1 : 0] = 0;
  return (check_string(str, client, nbC));
}

void	do_incantation(t_client *client, t_master *content)
{
  char	*players;

  players = check_level(client, content->clients);
  ssend(client->socket, "elevation en cours\n");
  client->level += (!players) ? 0 : 1;
  ssend_graphics(content, "pic %lu %lu %d %s\n",
		 client->pos[X], client->pos[Y], client->level, players);
  ssend(client->socket, "niveau actuel : %d\n", client->level);
  incantation_graphic(client, content, players);
  if (players)
    free(players);
}

void	incantation(char UNUSED*params,
		    t_client *client,
		    t_master *content)
{
  do_incantation(client, content);
}
