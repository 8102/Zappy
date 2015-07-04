/*
** direction.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 24 19:02:16 2015 Hugo Prenat
** Last update Sat Jul  4 01:45:55 2015 Hugo Prenat
*/

#include "zappy.h"

void	go_south_west(t_master *content, t_client *client,
		      e_Orientation orient)
{
  if (orient == SOUTH)
    {
      if (client->pos[X] == content->width - 1)
	set_pos(content, client, 0, client->pos[Y]);
      else
	set_pos(content, client, client->pos[X] + 1, client->pos[Y]);
    }
  else
    {
      if (client->pos[Y] == 0)
	set_pos(content, client, client->pos[X], content->width - 1);
      else
	set_pos(content, client, client->pos[X], client->pos[Y] - 1);
    }
}

void	change_pos(t_master *content, t_client *client, e_Orientation orient)
{
  if (orient == NORTH)
    {
      if (client->pos[X] == 0)
	set_pos(content, client, content->width - 1, client->pos[Y]);
      else
	set_pos(content, client, client->pos[X] - 1, client->pos[Y]);
    }
  else if (orient == EAST)
    {
      if (client->pos[Y] == content->height - 1)
	set_pos(content, client, client->pos[X], 0);
      else
	set_pos(content, client, client->pos[X], client->pos[Y] + 1);
    }
  else
    go_south_west(content, client, orient);
}

void		avance(char UNUSED*params,
		       t_client *client,
		       t_master *content)
{
  timespec_add(client->clock, content->time.delays[AVANCE], true);
  change_pos(content, client, client->orient);
  ssend_graphics(content, "ppo %d %lu %lu %d\n", client->id, client->pos[X],
		 client->pos[Y], client->orient);
  ssend(client->socket, "ok\n");
}

void		droite(char UNUSED*params,
		       t_client *client,
		       t_master *content)
{
  timespec_add(client->clock, content->time.delays[DROITE], true);
  if (client->orient != WEST)
    client->orient++;
  else
    client->orient = NORTH;
  ssend_graphics(content, "ppo %d %lu %lu %d\n", client->id, client->pos[X],
		 client->pos[Y], client->orient);
  ssend(client->socket, "ok\n");
}

void		gauche(char UNUSED*params,
		       t_client *client,
		       t_master *content)
{
  timespec_add(client->clock, content->time.delays[GAUCHE], true);
  if (client->orient != NORTH)
    client->orient--;
  else
    client->orient = WEST;
  ssend_graphics(content, "ppo %d %lu %lu %d\n", client->id, client->pos[X],
		 client->pos[Y], client->orient);
  ssend(client->socket, "ok\n");
}
