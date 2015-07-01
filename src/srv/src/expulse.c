/*
** expulse.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 29 17:18:03 2015 Hugo Prenat
** Last update Tue Jun 30 17:38:58 2015 Hugo Prenat
*/

#include "zappy.h"

void		expulse(char UNUSED*params,
			t_client *client,
			t_master *content)
{
  t_client	*tmp;
  int		orient;

  tmp = content->clients;
  orient = client->orient - 2;
  if (client->trigger[GRAPHIC])
    ssend(client->socket, "pex #%d\n", client->id);
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
}
