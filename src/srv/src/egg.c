/*
** egg.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 23 18:04:19 2015 Hugo Prenat
** Last update Tue Jun 23 19:21:52 2015 Hugo Prenat
*/

#include "zappy.h"

void		push_egg(t_egg **list, t_egg *elem)
{
  t_egg	*it;
  t_egg	*save;
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

void		pop_egg(t_egg **list, t_egg *elem)
{
  t_egg	*it;
  t_egg	*prev;

  if (!(*list))
    return ;
  it = *list;
  prev = it;
  while (it)
    {
      if (it == elem)
	{
	  if (prev != it)
	    prev->next = prev->next->next;
	  else
	    *list = (*list)->next;
	  it->next = NULL;
    free(elem);
    return ;
	}
      if (it != *list)
	prev = prev->next;
      it = it->next;
    }
}

void	add_egg(t_team *team, size_t x, size_t y, int id)
{
  t_egg	*egg;

  if (!(egg = malloc(sizeof(t_egg))))
    error("malloc");
  egg->pos[0] = x;
  egg->pos[1] = y;
  egg->id_player = id;
  push_egg(&team->eggs, egg);
}
