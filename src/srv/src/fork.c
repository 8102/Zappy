/*
** fork.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 30 21:06:34 2015 Hugo Prenat
** Last update Sun Jul  5 18:49:51 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		_fork(char UNUSED*params,
		      t_client *client,
		      t_master *content)
{
  double	z;
  timespec_t	*time;
  t_egg		*egg;

  timespec_add(client->clock, content->time.delays[FORK], true);
  ssend(client->socket, "ok\n");
  ssend_graphics(content, "pfk %d\n", client->id);
  egg = add_egg(client->team, content, client->pos, client->id);
  z = (600 / (double)(content->delay)) * 1000000;
  time = timespec_convert((ull)z);
  timespec_add(client->clock, time, true);
  ssend_graphics(content, "eht %d\n", egg->id);
  egg->eclos = true;
  client->team->slot++;
  timespec_release(time);
}
