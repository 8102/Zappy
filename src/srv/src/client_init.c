/*
** client_init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Mon Jun 22 22:25:56 2015 Hugo Prenat
** Last update Sun Jul  5 18:41:08 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		get_egg_pos(t_team *team, size_t *x, size_t *y, t_master *content)
{
  t_egg         *tmp;

  for (tmp = team->eggs; tmp; tmp = tmp->next)
    {
      if (tmp->eclos)
	{
	  *x = tmp->pos[X];
	  *y = tmp->pos[Y];
	  pop_egg(&team->eggs, tmp);
	  break ;
	}
    }
  *x = rand() % content->width;
  *y = rand() % content->height;
}

void		place_player(t_master *content, t_client *client)
{
  size_t	x;
  size_t	y;

  get_egg_pos(client->team, &x, &y, content);
  set_pos(content, client, x, y);
  client->placed = true;
  client->resources[MEAL] = 10;
  client->resources[LINEMATE] = 0;
  client->resources[DERAUMERE] = 0;
  client->resources[SIBUR] = 0;
  client->resources[MENDIANE] = 0;
  client->resources[PHIRAS] = 0;
  client->resources[THYSTAME] = 0;
  client->trigger[AUTH] = true;
  client->level = 1;
  ssend_graphics(content, "pnw %d %lu %lu %d %d %s\n", client->id,
  		 client->pos[X], client->pos[Y], client->orient,
  		 client->level, client->team->name);
  ssend_graphics(content, "pin %d %lu %lu %d %d %d %d %d %d\n",
  		 client->id, client->pos[X], client->pos[Y],
  		 client->resources[MEAL], client->resources[LINEMATE],
  		 client->resources[DERAUMERE], client->resources[SIBUR],
  		 client->resources[MENDIANE], client->resources[MENDIANE],
  		 client->resources[PHIRAS], client->resources[THYSTAME]);
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
