/*
** client_init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 22 22:25:56 2015 Hugo Prenat
** Last update Tue Jun 23 14:56:00 2015 Emmanuel Chambon
*/

#include "zappy.h"

bool		place_pos(t_master *content, size_t x, size_t y)
{
  t_client	*tmp;

  tmp = content->clients;
  while (tmp)
    {
      printf("hello\n");
      if (tmp->pos[X] == x && tmp->pos[Y] == y)
	return (false);
      tmp = tmp->next;
    }
  return (true);
}

void		place_player(t_master *content, t_client *client)
{
  size_t	x;
  size_t	y;

  x = rand() % content->width;
  y = rand() % content->height;
  while (!place_pos(content, x, y))
    {
      x = rand() % content->width;
      y = rand() % content->height;
    }
  client->pos[X] = x;
  client->pos[y] = y;
  client->resources[MEAL] = 0;
  client->resources[LINEMATE] = 0;
  client->resources[DERAUMERE] = 0;
  client->resources[SIBUR] = 0;
  client->resources[MENDIANE] = 0;
  client->resources[PHIRAS] = 0;
  client->resources[THYSTAME] = 0;
  client->trigger[AUTH] = true;
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
