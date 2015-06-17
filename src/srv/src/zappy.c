/*
** zappy.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 20:14:21 2015 Emmanuel Chambon
** Last update Wed Jun 17 21:34:25 2015 Emmanuel Chambon
*/

#include "zappy.h"

int		init_zappy(t_all *content, int ac, char **av)
{
  if ((content->teams = malloc(sizeof(*content->teams) * 1)) == NULL)
    error("malloc");
  content->teams[0].slot = -1;
  content->max_clients = 0;
  content->width = 0;
  content->height = 0;
  content->delay = 0;
  content->clients = NULL;
  if (check_param(ac, av, content) == -1)
    {
      fprintf(stderr,
	      "Usage: %s [-p port] [-x world_x] [-y world_y]"
	      " [-c max_clients] [-t speed] -n team_name_1 team_name_2 ...\n",
	      av[0]);
      return (-1);
  }
  init_server(&(content->server), content->port);
  return (0);
}

void		release_zappy(t_all *content)
{
  release_server(&(content->server));
}
