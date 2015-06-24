/*
** welcome.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 15:01:28 2015 Emmanuel Chambon
** Last update Wed Jun 24 14:01:08 2015 Emmanuel Chambon
*/

#include "zappy.h"

t_team		*find_team(char *team_name, t_master *content)
{
  t_team	*tmp;

  for (tmp = content->teams; tmp; tmp = tmp->next)
    {
      if (!(strncmp(tmp->name, team_name, strlen(tmp->name)))
	  && strlen(team_name) == strlen(tmp->name))
	return (tmp);
    }
  return (NULL);
}

void		select_team(char *team, t_client *client, t_master *content)
{
  t_team	*tm;

  if (!(tm = find_team(team, content)))
    ssend(client->socket, "0\n");
  else
    {
      if (tm->slot == 0)
	ssend(client->socket, "0\n");
      else
	{
	  ssend(client->socket, "%d\n", tm->slot);
	  client->team = tm;
	  place_player(client, client->team);
	  client->team->slot--;
	}
    }
  ssend(client->socket, "%d %d\n", content->width, content->height);
}
