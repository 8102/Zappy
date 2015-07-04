/*
** expulse.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 29 17:18:03 2015 Hugo Prenat
** Last update Sat Jul  4 01:25:49 2015 Hugo Prenat
*/

#include "zappy.h"

void		send_new_pos(t_master *content, int id)
{
  t_client	*cur;
  t_client	*tmp;

  cur = content->clients;
  while (cur)
    {
      if (cur->trigger[GRAPHIC] == true)
	{
	  ssend(cur->socket, "pex %d\n", id);
	  tmp = content->clients;
	  while (tmp)
	    {
	      ssend(cur->socket, "ppo %d %lu %lu %d\n", tmp->id,
		    tmp->pos[X], tmp->pos[Y], tmp->orient);
	      tmp = tmp->next;
	    }
	}
      cur = cur->next;
    }
}

void		expulse(char UNUSED*params,
			t_client *client,
			t_master *content)
{
  t_client	*tmp;
  int		orient;

  timespec_add(client->clock, content->time.delays[EXPULSE], true);
  tmp = content->clients;
  orient = client->orient - 2;
  if (client->trigger[GRAPHIC])
    ssend(client->socket, "pex %d\n", client->id);
  if (orient == -1)
    orient = SOUTH;
  else if (orient == 0)
    orient = WEST;
  else
    orient = orient;
  while (tmp)
    {
      if (client->pos[X] == tmp->pos[X] && client->pos[Y] == tmp->pos[Y] &&
	  client->id != tmp->id)
	{
	  change_pos(content, tmp, client->orient);
	  ssend(tmp->socket, "deplacement: %d\n", orient);
	}
      tmp = tmp->next;
    }
  send_new_pos(content, client->id);
}
