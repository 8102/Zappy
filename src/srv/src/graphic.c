/*
** graphic.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 24 17:11:21 2015 Hugo Prenat
** Last update Sun Jul  5 03:20:02 2015 Hugo Prenat
*/

#include "zappy.h"

void		send_map(t_client *client, t_master *content)
{
  t_case	*case_tmp;

  case_tmp = content->cases;
  while (case_tmp)
    {
      ssend(client->socket, "bct %lu %lu %d %d %d %d %d %d %d\n",
	    case_tmp->x, case_tmp->y, case_tmp->content[1],
	    case_tmp->content[2], case_tmp->content[3], case_tmp->content[4],
	    case_tmp->content[5], case_tmp->content[6], case_tmp->content[7]);
      case_tmp = case_tmp->next;
    }
}

void		send_team(t_client *client, t_master *content)
{
  t_team	*team_tmp;

  team_tmp = content->teams;
  while (team_tmp)
    {
      ssend(client->socket, "tna %s\n", team_tmp->name);
      team_tmp = team_tmp->next;
    }
}

void		send_player(t_client *client, t_master *content)
{
  t_client	*client_tmp;

  client_tmp = content->clients;
  while (client_tmp)
    {
      if (client_tmp->trigger[AUTH])
	ssend(client->socket, "pnw %d %lu %lu %d %d %s\n", client_tmp->id,
	      client_tmp->pos[X], client_tmp->pos[Y], client_tmp->orient,
	      client_tmp->level, client_tmp->team->name);
      client_tmp = client_tmp->next;
    }
}

void		send_egg(t_client *client, t_master *content)
{
  t_team	*team_tmp;
  t_egg		*egg_tmp;

  team_tmp = content->teams;
  while (team_tmp)
    {
      egg_tmp = team_tmp->eggs;
      while (egg_tmp)
	{
	  ssend(client->socket, "enw %d %d %lu %lu\n", egg_tmp->nbr,
		egg_tmp->id, egg_tmp->pos[X], egg_tmp->pos[Y]);
	  egg_tmp = egg_tmp->next;
	}
      team_tmp = team_tmp->next;
    }
}

void	graphic(char UNUSED*params,
		t_client *client, t_master *content)
{
  client->trigger[GRAPHIC] = true;
  ssend(client->socket, "msz %lu %lu\n", content->width, content->height);
  ssend(client->socket, "sgt %d\n", content->delay);
  send_map(client, content);
  send_team(client, content);
  send_player(client, content);
  send_egg(client, content);
}
