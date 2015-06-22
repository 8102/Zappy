/*
** client_init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 22 22:25:56 2015 Hugo Prenat
** Last update Mon Jun 22 23:00:43 2015 Hugo Prenat
*/

#include "zappy.h"

bool		place_pos(t_master *content, size_t x, size_t y)
{
  t_client	*tmp;

  tmp = content->clients;
  while (tmp)
    {
      if (tmp->x == x && tmp->y == y)
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
}

void	init_client(t_master *content, t_client *client)
{
  client->orient = NORTH;
  client->buffer = cb_init();
  client->recv = rb_init();
  client->auth = false;
  client->graphic = false;
  client->meal = 0;
  client->linemate = 0;
  client->deraumere = 0;
  client->sibur = 0;
  client->mendiane = 0;
  client->phiras = 0;
  client->thystame = 0;
  place_player(content, client);
}
