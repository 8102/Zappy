/*
** client_init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 22 22:25:56 2015 Hugo Prenat
** Last update Fri Jul  3 03:42:17 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		place_player(t_master *content, t_client *client)
{
  size_t	x;
  size_t	y;

  x = rand() % content->width;
  y = rand() % content->height;
  set_pos(content, client, x, y);
  client->placed = true;
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

void	init_client(t_client *client, t_master *content)
{
  content->nbr_player++;
  client->id = content->nbr_player;
  client->orient = NORTH;
  client->buffer = cb_init();
  client->recv = rb_init();
  client->clock = timespec_init(NULL);
  client->trigger[AUTH] = false;
  client->trigger[GRAPHIC] = false;
  client->team = NULL;
  client->placed = false;
}
