/*
** case.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Thu Jun 18 22:08:05 2015 Hugo Prenat
** Last update Thu Jul  2 21:44:10 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		push_case(t_case **list, t_case *elem, t_case **last)
{
  t_case	*it;
  t_case	*save;
  bool		stop;

  if (*list == NULL)
    {
      elem->prev = NULL;
      elem->next = NULL;
      *list = elem;
      return ;
    }
  stop = true;
  it = *last;
  while (it && stop)
    {
      if (it->next)
	it = it->next;
      else
	stop = false;
    }
  save = it->next;
  it->next = elem;
  elem->prev = it;
  elem->next = save;
}

int		add_one_case(t_master *content, size_t x, size_t y)
{
  t_case	*new;
  static t_case *last = NULL;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->x = x;
  new->y = y;
  new->meal = rand() % 2;
  new->linemate = rand() % 2;
  new->deraumere = rand() % 2;
  new->sibur = rand() % 2;
  new->mendiane = rand() % 2;
  new->phiras = rand() % 2;
  new->thystame = rand() % 2;
  new->nbr_player = 0;
  push_case(&content->cases, new, &last);
  last = new;
  return (0);
}

int	create_map(t_master *content)
{
  int	x;
  int	y;

  x = 0;
  while (x != content->width)
    {
      y = 0;
      while (y != content->height)
	{
	  add_one_case(content, x, y);
	  y++;
	}
      x++;
    }
  return (0);
}
