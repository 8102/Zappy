/*
** init.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Wed Jun 17 18:04:44 2015 Hugo Prenat
** Last update Sat Jul  4 05:19:16 2015 Emmanuel Chambon
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

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->name = team;
  new->leveled_pl = 0;
  new->slot = content->max_clients;
  new->eggs = NULL;
  push_team(&content->teams, new);
  return (0);
}

void		multiple_team(char *team)
{
  fprintf(stderr,
	  "%sDuplicate team: {%s}. Will only be counted once%s\n",
	  BOLDRED, team, RESET);
}

bool		add_team(char **av, int ac, t_master *content)
{
  int		i;
  t_team	*tmp;

  i = optind - 1;
  if (av[i][0] == '-')
    return (false);
  while (i < ac)
    {
      if (av[i][0] == '-')
	return (true);
      for (tmp = content->teams; tmp; tmp = tmp->next)
	{
	  if (!strcmp(tmp->name, av[i]))
	    {
	      multiple_team(tmp->name);
	      break ;
	    }
	}
      if (!tmp)
	add_one_team(av[i], content);
      i++;
    }
  return (true);
}
