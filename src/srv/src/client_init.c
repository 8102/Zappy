/*
** client_init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 22 22:25:56 2015 Hugo Prenat
** Last update Wed Jun 24 13:32:49 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		place_pos(t_client *client, t_team *team)
{
  t_egg		*tmp;

  tmp = team->eggs;
  while (tmp->next)
    tmp = tmp->next;
  client->pos[X] = tmp->pos[X];
  client->pos[Y] = tmp->pos[Y];
  pop_egg(&team->eggs, tmp);
}

void		place_player(t_client *client, t_team *team)
{
  place_pos(client, team);
  client->resources[MEAL] = 0;
  client->resources[LINEMATE] = 0;
  client->resources[DERAUMERE] = 0;
  client->resources[SIBUR] = 0;
  client->resources[MENDIANE] = 0;
  client->resources[PHIRAS] = 0;
  client->resources[THYSTAME] = 0;
  client->trigger[AUTH] = true;
  client->level = 1;
}

void	init_client(t_client *client)
{
  client->orient = NORTH;
  client->buffer = cb_init();
  client->recv = rb_init();
  client->trigger[AUTH] = false;
  client->trigger[GRAPHIC] = false;
  client->team = NULL;
}
