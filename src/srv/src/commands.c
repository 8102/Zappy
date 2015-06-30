/*
** commands.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 08:31:10 2015 Emmanuel Chambon
** Last update Wed Jun 24 15:26:13 2015 Hugo Prenat
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

void			prend(char *params,
			      t_client *client,
			      t_master *content)
{
  t_case		*position;

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

void			pose(char *params,
			     t_client *client,
			     UNUSED t_master *content)
{
  t_case		*position;

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

void			broadcast(char *params,
				  t_client *client,
				  t_master *content)
{
  t_client		*parsing;

  parsing = content->clients;
  ssend(client->socket, "ok\n");
  while (parsing)
    {
      if (parsing->id != client->id)
	ssend(parsing->socket, "message %d, %s",
	      checkBasicCase(client, parsing, content), params);
      parsing = parsing->next;
    }
}

void			incantation(char UNUSED*params,
				    t_client *client,
				    UNUSED t_master *content)
{
  ssend(client->socket, "elevation en cours\nniveau actuel : %d\n", client->level);
}

void			_fork(char UNUSED*params,
			      t_client *client,
			      UNUSED t_master *content)
{
  ssend(client->socket, "ok\n");
}

void			connect_nbr(char UNUSED*params,
				    t_client *client,
				    UNUSED t_master *content)
{
  ssend(client->socket, "%d\n", client->team->slot);
}

void			msz(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void		bct(char *params,
				    t_client *client,
				    t_master *content)
{
//   char	*tmp;
//   int		i;
//
//   i = 0;
//   tmp = params;
//   while ((tmp = index(tmp, ' ')) != NULL)
//     i++;
// printf("params === {%s} %d\n", params, i);
  // if (!params)
	// 	{
	// 		ssend(client->socket, "suc\n");
	// 		return ;
	// 	}
	// ssend(client->socket, "ok\n");
}

void			mct(char UNUSED*params,
				    t_client *client,
				    t_master *content)
{
  send_map(client, content);
}

void			tna(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void			ppo(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void			plv(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void			pin(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void			sgt(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}

void			sst(char UNUSED*params,
				    t_client UNUSED*client,
				    UNUSED t_master *content)
{

}
