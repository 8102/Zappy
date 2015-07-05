/*
** zappy.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 20:14:21 2015 Emmanuel Chambon
** Last update Sun Jul  5 02:00:27 2015 Emmanuel Chambon
*/

#include "zappy.h"

int		init_zappy(t_master *content, int ac, char **av)
{
  srand(time(NULL));
  content->max_clients = 0;
  content->width = 0;
  content->height = 0;
  content->delay = 0;
  content->nbr_egg = 0;
  content->nbr_player = 0;
  content->port = NULL;
  content->teams = NULL;
  content->clients = NULL;
  content->cases = NULL;
  if (!get_param(ac, av, content) || !check_param(content))
    return (usage(av[0]));
  set_timeout(content);
  set_delays(content);
  create_map(content);
  minerals_gen(content);
  init_server(&(content->server), content->port);
  print_creation(content);
  return (0);
}

void		release_eggs(t_egg **list)
{
  t_egg		*it;
  t_egg		*elem;

  if (!(*list))
    return ;
  it = *list;
  while (it != NULL)
    {
      elem = it;
      it = it->next;
      free(elem);
    }
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
      release_eggs(&elem->eggs);
      free(elem);
    }
}

void		del_case(t_case **list)
{
  t_case	*it;
  t_case	*elem;

  if (!(*list))
    return ;
  it = *list;
  while (it != NULL)
    {
      elem = it;
      it = it->next;
      free(elem);
    }
}

void		release_zappy(t_master *content)
{
  release_clients(&(content->clients));
  release_delays(content);
  release_server(&(content->server));
  del_team(&content->teams);
  del_case(&content->cases);
}
