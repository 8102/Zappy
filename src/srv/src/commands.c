/*
** commands.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 08:31:10 2015 Emmanuel Chambon
** Last update Thu Jul  2 15:29:11 2015 Hugo Prenat
*/

#include "zappy.h"

void			inventaire(char UNUSED*params,
				   t_client *client,
				   UNUSED t_master *content)
{
  ssend(client->socket, "{linemate %d, deraumère %d, sibur %d, mendiane %d,\
 phiras %d, thystame %d}\n", client->resources[LINEMATE],
	client->resources[DERAUMERE],
	client->resources[SIBUR],
	client->resources[MENDIANE],
	client->resources[PHIRAS],
	client->resources[THYSTAME]);
}

void		broadcast(char *params,
			  t_client *client,
			  t_master *content)
{
  t_client	*parsing;

  parsing = content->clients;
  ssend(client->socket, "ok\n");
  while (parsing)
    {
      if (parsing->id != client->id)
	ssend(parsing->socket, "message %d,%s\n",
	      checkBasicCase(client, parsing, content), params);
      if (parsing->trigger[GRAPHIC])
	ssend(parsing->socket, "pbc %d %s\n", client->id, params);
      parsing = parsing->next;
    }
}

void	connect_nbr(char UNUSED*params,
		    t_client *client,
		    UNUSED t_master *content)
{
  ssend(client->socket, "%d\n", client->team->slot);
}

void		tna(char UNUSED*params,
		    t_client UNUSED*client,
		    t_master *content)
{
  t_team	*allT;

  allT = content->teams;
  while (allT)
    {
      ssend(client->socket, "tna %s\n", allT->name);
      allT = allT->next;
    }
}
