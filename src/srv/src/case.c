/*
** case.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Thu Jun 18 22:08:05 2015 Hugo Prenat
** Last update Sun Jul  5 23:12:01 2015 Hugo Prenat
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

void		set_mineral(int index, ull quantity, t_master *content)
{
  ull		i;
  t_case	*tmp;

  for (i = 0; i < quantity; i++)
    {
      if (!(tmp = getCaseFromCoord(rand() % content->width,
				   rand() % content->height,
				   content->cases)))
	continue ;
      tmp->content[index]+= 1;
    }
}

void		minerals_gen(t_master *content)
{
  ull		map;

  map = content->width * content->height * ((rand() % 3) + 1);
  set_mineral(((int)LINEMATE) + 1, map / 40 * 10, content);
  set_mineral(((int)DERAUMERE) + 1, map / 40 * 9, content);
  set_mineral(((int)SIBUR) + 1, map / 40 * 9, content);
  set_mineral(((int)MENDIANE) + 1, map / 40 * 6, content);
  set_mineral(((int)PHIRAS) + 1, map / 40 * 6, content);
  set_mineral(((int)THYSTAME) + 1, 1, content);
  set_mineral(((int)MEAL) + 1, map / 100 * (rand() % 10), content);
}

int		add_one_case(t_master *content, size_t x, size_t y)
{
  t_case	*new;
  static t_case *last = NULL;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (-1);
  new->x = x;
  new->y = y;
  new->content[0] = 0;
  new->content[1] = 0;
  new->content[2] = 0;
  new->content[3] = 0;
  new->content[4] = 0;
  new->content[5] = 0;
  new->content[6] = 0;
  new->content[7] = 0;
  push_case(&content->cases, new, &last);
  last = new;
  return (0);
}

int		create_map(t_master *content)
{
  size_t	x;
  size_t	y;

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
