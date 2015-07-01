/*
** commands.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 08:31:10 2015 Emmanuel Chambon
** Last update Tue Jun 30 16:37:03 2015 Hugo Prenat
*/

#include "zappy.h"

void			voir(char UNUSED*params,
			     t_client *client,
			     t_master *content)
{
  select_position_watch(client, content);
}

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

void		prend(char *params,
		      t_client *client,
		      t_master *content)
{
  t_case	*position;

  if (!(position = getCaseFromCoord(client->pos[0], client->pos[1],
				    content->cases)))
    ssend(client->socket, "ko\n");
  else
    {
      if (checkPossibleTake(position, params, client) == 0)
	ssend(client->socket, "ko\n");
      else
	ssend(client->socket, "ok\n");
    }
}

void		pose(char *params,
		     t_client *client,
		     UNUSED t_master *content)
{
  t_case	*position;

  if (!(position = getCaseFromCoord(client->pos[0], client->pos[1],
				    content->cases)))
    ssend(client->socket, "ko\n");
  else
    {
      if (checkPossibleSend(position, params, client) == 0)
	ssend(client->socket, "ko\n");
      else
	ssend(client->socket, "ok\n");
    }
}

void		broadcast(char *params,
			  t_client *client,
			  t_master *content)
{
  t_client	*parsing;

  parsing = content->clients;
  ssend(client->socket, "ok\n");
  if (client->trigger[GRAPHIC])
    ssend(client->socket, "pbc #%d %s", client->id, params);
  while (parsing)
    {
      if (parsing->id != client->id)
	ssend(parsing->socket, "message %d, %s",
	      checkBasicCase(client, parsing, content), params);
      parsing = parsing->next;
    }
}

void	incantation(char UNUSED*params,
		    t_client *client,
		    t_master *content)
{
  do_incantation(client, content);
}

void	connect_nbr(char UNUSED*params,
		    t_client *client,
		    UNUSED t_master *content)
{
  ssend(client->socket, "%d\n", client->team->slot);
}

void	msz(char UNUSED*params,
	    t_client UNUSED*client,
	    UNUSED t_master *content)
{
  ssend(client->socket, "msz %ul %ul\n", content->width, content->height);
}

void		bct(char *params,
		    t_client *client,
		    t_master *content)
{
  int		x;
  int		y;
  int		i;
  t_case	*case_tmp;

  if (!params || !params[0])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  x = atoi(params);
  i = 0;
  while (params[i] && params[i++] != ' ');
  if (!params[i])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  y = atoi(&params[i]);
  (!(case_tmp = getCaseFromCoord(x, y, content->cases))) ?
    ssend(client->socket, "sbp\n") :
    ssend(client->socket, "bct %d %d %d %d %d %d %d %d %d\n",
	  case_tmp->x, case_tmp->y, case_tmp->meal, case_tmp->linemate,
	  case_tmp->deraumere, case_tmp->sibur, case_tmp->mendiane,
	  case_tmp->phiras, case_tmp->thystame);
}

void	mct(char UNUSED*params,
	    t_client *client,
	    t_master *content)
{
  send_map(client, content);
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
	  ssend(client->socket, "plv #%d %d\n", nbrP, clients->level);
	  return ;
	}
      clients = clients->next;
    }
  ssend(client->socket, "sbp\n");
}

void	pin(char *params,
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
	  ssend(client->socket, "pin #%d %ul %ul %d %d %d %d %d %d \n",
		clients->id, clients->pos[0], clients->pos[1], clients->resources[MEAL],
		clients->resources[LINEMATE], clients->resources[DERAUMERE],
		clients->resources[SIBUR], clients->resources[MENDIANE],
		clients->resources[MENDIANE], clients->resources[PHIRAS],
		clients->resources[THYSTAME]);
	  return ;
	}
      clients = clients->next;
    }
  ssend(client->socket, "sbp\n");
}

void	sgt(char UNUSED*params,
	    t_client *client,
	    t_master *content)
{
  ssend(client->socket, "sgt %d\n", content->delay);
}

void	sst(char *params,
	    t_client UNUSED*client,
	    t_master *content)
{
  int	newT;

  if (!params || !params[0])
    {
      ssend(client->socket, "sbp\n");
      return ;
    }
  newT = atoi(params);
  ssend(client->socket, "sgt %d\n", newT);
  content->delay = newT;
}
