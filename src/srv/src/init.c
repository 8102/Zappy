/*
** init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 17 18:04:44 2015 Hugo Prenat
** Last update Wed Jul  1 18:49:41 2015 Hugo Prenat
*/

#include "zappy.h"

void		push_team(t_team **list, t_team *elem)
{
  t_team	*it;
  t_team	*save;
  bool		stop;

  if (*list == NULL)
    {
      elem->next = NULL;
      *list = elem;
      return ;
    }
  stop = true;
  it = *list;
  while (it && stop)
    {
      if (it->next)
	it = it->next;
      else
	stop = false;
    }
  save = it->next;
  it->next = elem;
  elem->next = save;
}

int		add_one_team(char *team, t_master *content)
{
  t_team	*new;
  int		i;
  size_t	pos[2];

  i = 0;
  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->name = team;
  new->slot = content->max_clients;
  new->eggs = NULL;
  while (i < content->max_clients)
    {
      pos[0] = rand() % content->width;
      pos[1] = rand() % content->height;
      add_egg(new, content, pos, -1);
      i++;
    }
  push_team(&content->teams, new);
  return (0);
}

int	add_team(char **av, int ac, t_master *content)
{
  int	i;

  i = optind - 1;
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  optind = i - 1;
	  return (0);
	}
      add_one_team(av[i], content);
      i++;
    }
  return (0);
}

int	check_param(int ac, char **av, t_master *content)
{
  int	opt;
  int	ret;

  ret = 0;
  while ((opt = getopt(ac, av, "p:x:y:c:t:n:")) != -1)
    {
      if (opt == '?')
	ret = -1;
      if (opt == 'p')
	content->port = optarg;
      if (opt == 'x')
	content->width = atoi(optarg);
      if (opt == 'y')
	content->height = atoi(optarg);
      if (opt == 'c')
	content->max_clients = atoi(optarg);
      if (opt == 't')
	content->delay = atoi(optarg);
      if (opt == 'n')
	ret = add_team(av, ac, content);
    }
  if (ac < 13)
    ret = -1;
  return (ret);
}
