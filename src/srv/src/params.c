/*
** params.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Sat Jul  4 05:18:34 2015 Emmanuel Chambon
** Last update Sat Jul  4 05:19:10 2015 Emmanuel Chambon
*/

#include "zappy.h"

bool	check_param(t_master *content)
{
  if (!content->port)
    content->port = strdup("4242");
  if (!content->width)
    content->width = 20;
  if (!content->height)
    content->height = 20;
  if (!content->max_clients)
    content->max_clients = 1;
  if (!content->delay)
    content->delay = 100;
  if (!content->teams)
    return (false);
  return (true);
}

bool	get_param(int ac, char **av, t_master *content)
{
  int	opt;

  while ((opt = getopt(ac, av, "p:x:y:c:t:n:")) != -1) {
    if (opt == 'p')
      content->port = optarg;
    else if (opt == 'x')
      content->width = (size_t)atol(optarg);
    else if (opt == 'y')
      content->height = (size_t)atol(optarg);
    else if (opt == 'c')
      content->max_clients = atoi(optarg);
    else if (opt == 't')
      content->delay = atoi(optarg);
    else if (opt == 'n')
      {
	if (!add_team(av, ac, content))
	  return (false);
      }
    else
      return (false);
  }
  return (true);
}
