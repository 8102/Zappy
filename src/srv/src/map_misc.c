/*
** map_misc.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Thu Jul  2 15:40:37 2015 Hugo Prenat
** Last update Fri Jul  3 22:40:01 2015 Hugo Prenat
*/

#include "zappy.h"

void	msz(char UNUSED*params,
	    t_client UNUSED*client,
	    UNUSED t_master *content)
{
  ssend(client->socket, "msz %u %u\n", content->width, content->height);
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

void		prend(char *params,
		      t_client *client,
		      t_master *content)
{
  t_case	*position;
  int		resource;

  timespec_add(client->clock, content->time.delays[PREND], true);
  if (!(position = getCaseFromCoord(client->pos[0], client->pos[1],
				    content->cases)))
    ssend(client->socket, "ko\n");
  else
    {
      if ((resource = checkPossibleTake(position, params, client)) == -1)
	ssend(client->socket, "ko\n");
      else
	{
	  ssend(client->socket, "ok\n");
	  prend_graphic(client, content, resource);
	}
    }
}

void		pose(char *params,
		     t_client *client,
		     t_master *content)
{
  t_case	*position;
  int		resource;

  timespec_add(client->clock, content->time.delays[POSE], true);
  if (!(position = getCaseFromCoord(client->pos[0], client->pos[1],
				    content->cases)))
    ssend(client->socket, "ko\n");
  else
    {
      if ((resource = checkPossibleSend(position, params, client)) == 0)
	ssend(client->socket, "ko\n");
      else
	{
	  ssend(client->socket, "ok\n");
	  pose_graphic(client, content, resource);
	}
    }
}
