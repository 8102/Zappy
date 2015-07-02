/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
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
  if (!(str = malloc(1)))
    return (NULL);
  str[0] = 0;
  while (clients)
    {
      if (client->id != clients->id && clients->pos[0] == client->pos[0] &&
	  clients->pos[1] == client->pos[1] && client->level == clients->level)
	{
	  if (!(nbr = transform_int(clients->id)))
	    return (NULL);
	  str = realloc(str, strlen(str) + strlen(nbr) + 2);
	  strcat(str, nbr);
	  strcat(str, " ");
	  free(nbr);
	  nbC++;
	}
      clients = clients->next;
    }
  str[strlen(str) - 1] = 0;
  return (check_string(str, client, nbC));
}

void	do_incantation(t_client *client, t_master *content)
{
  char	*players;

  players = check_level(client, content->clients);
  if (client->trigger[GRAPHIC])
    players ? ssend(client->socket, "pic %u %u %d %s\n",
		    client->pos[0], client->pos[1], client->level, players) :
      ssend(client->socket, "pic %u %u %d\n", client->pos[0], client->pos[1],
	    client->level);
  ssend(client->socket, "elevation en cours\nniveau actuel : %d\n",
	client->level);
  if (client->trigger[GRAPHIC])
    {
      if (!players)
	ssend(client->socket, "pie %u %u %d\n", client->pos[0], client->pos[1],
	      0);
      else
	ssend(client->socket, "pie %u %u %d\n", client->pos[0], client->pos[1],
	      check_stones(client, getCaseFromCoord
			   (client->pos[0], client->pos[1], content->cases),
			   content->clients));
    }
  if (players)
    free(players);
}

void	incantation(char UNUSED*params,
		    t_client *client,
		    t_master *content)
{
  do_incantation(client, content);
}
