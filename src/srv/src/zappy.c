/*
** zappy.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 20:14:21 2015 Emmanuel Chambon
** Last update Thu Jun 18 14:50:11 2015 Hugo Prenat
*/

#include "zappy.h"

int		init_zappy(t_all *content, int ac, char **av)
{
  content->max_clients = 0;
  content->width = 0;
  content->height = 0;
  content->delay = 0;
  content->teams = NULL;
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

void		del_team(t_team **list)
{
  t_team	*it;
  t_team	*elem;

  if (!(*list))
    return ;
  it = *list;
  while (it != NULL)
    {
      elem = it;
      it = it->next;
      free(elem);
    }
  return ;
}

void		release_zappy(t_all *content)
{
  release_server(&(content->server));
  del_team(&content->teams);
}
