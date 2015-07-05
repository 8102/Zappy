/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sun Jul  5 19:54:28 2015 Hugo Prenat
*/

#include "zappy.h"

void	pose_graphic(t_master *content, t_client *client, t_case *case_tmp,
		      int resource)
{
  ssend_graphics(content, "pdr %d %d\n", client->id, resource);
  ssend_graphics(content, "pin %d %lu %lu %d %d %d %d %d %d\n",
		 client->id, client->pos[X], client->pos[Y],
		 client->resources[MEAL], client->resources[LINEMATE],
		 client->resources[DERAUMERE], client->resources[SIBUR],
		 client->resources[MENDIANE], client->resources[PHIRAS],
		 client->resources[THYSTAME]);
  ssend_graphics(content, "bct %lu %lu %d %d %d %d %d %d %d\n",
		 case_tmp->x, case_tmp->y, case_tmp->content[1],
		 case_tmp->content[2], case_tmp->content[3],
		 case_tmp->content[4], case_tmp->content[5],
		 case_tmp->content[6], case_tmp->content[7]);
}

int		checkPossibleSend(t_case *position, char *param,
				  t_client *client)
{
  static char	*content[] = {"linemate", "deraumere", "sibur", "mendiane",
			      "phiras", "thystame", "nourriture", NULL};

  for (int i = 0; i <= 5; i++)
    {
      if (!strcmp(content[i], param) && position->content[i + 2] > 0)
	{
	  position->content[i + 2]++;
	  client->resources[i]--;
	  return (i + 1);
	}
    }
  if (!strcmp(content[MEAL], param) && position->content[1] > 0)
    	{
	  position->content[1]++;
	  client->resources[MEAL]--;
	  return (0);
	}
  return (-1);
}

void		pose(char *params,
		     t_client *client,
		     t_master *content)
{
  t_case	*position;
  int		resource;

  timespec_add(client->clock, content->time.delays[POSE], true);
  if (!params)
    {
      ssend(client->socket, "ko\n");
      return ;
    }
  position = getCaseFromCoord(client->pos[X], client->pos[Y], content->cases);
  if ((resource = checkPossibleSend(position, params, client)) == -1)
    ssend(client->socket, "ko\n");
  else
    {
      ssend(client->socket, "ok\n");
      pose_graphic(content, client, position, resource);
    }
}
