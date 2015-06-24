/*
** graphic.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 24 17:11:21 2015 Hugo Prenat
** Last update Thu Jun 25 00:24:15 2015 Hugo Prenat
*/

#include "zappy.h"

void	send_map(t_client *client, t_master *content)
{
  t_case	*case_tmp;

  case_tmp = content->cases;
  while (case_tmp)
  {
    ssend(client->socket, "bct %d %d %d %d %d %d %d %d %d\n",
	  case_tmp->x, case_tmp->y, case_tmp->meal, case_tmp->linemate,
	  case_tmp->deraumere, case_tmp->sibur, case_tmp->mendiane,
	  case_tmp->phiras, case_tmp->thystame);
    case_tmp = case_tmp->next;
  }
}

void	send_team(t_client *client, t_master *content)
{
  t_team	*team_tmp;

  team_tmp = content->teams;
  while (team_tmp)
  {
    ssend(client->socket, "tna %s\n", team_tmp->name);
    team_tmp = team_tmp->next;
  }
}

void	send_player(t_client *client, t_master *content)
{
  t_client	*client_tmp;

  client_tmp = content->clients;
  while (client_tmp)
  {
    ssend(client->socket, "pnw %d %d %d %d %d %s\n", client_tmp->id,
	  client_tmp->pos[0], client_tmp->pos[1], client_tmp->orient,
	  client_tmp->level, client_tmp->team->name);
    client_tmp = client_tmp->next;
  }
}

void	send_egg(t_client *client, t_master *content)
{
  t_egg		*egg_tmp;

  // egg_tmp = content->eggs;
  // while (egg_tmp)
  // {
  //   ssend(client->socket, "enw %d %d %d %d\n", egg_tmp->nbr, egg_tmp->id,
	//   egg_tmp->pos[0], egg_tmp->pos[1]);
  //   egg_tmp = egg_tmp->next;
  // }
}

void		graphic(char UNUSED*params,
			t_client *client, t_master *content)
{
  client->trigger[GRAPHIC] = true;
  ssend(client->socket, "msz %d %d\n", content->width, content->height);
  ssend(client->socket, "sgt %d\n", content->delay);
  send_map(client, content);
  send_team(client, content);
  send_player(client, content);
  send_egg(client, content);
}
