/*
** egg.c for Zappy in /home/patoche/Rendu/Unix/PSU_2014_zappy/src/srv/src/
**
** Made by Hugo Prenat
** Login   <prenat_h@epitech.eu>
**
** Started on  Tue Jun 23 18:04:19 2015 Hugo Prenat
** Last update Tue Jun 30 23:12:34 2015 Hugo Prenat
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

void	add_egg(t_team *team, t_master *content, size_t pos[2], int id)
{
  t_egg	*egg;
  t_client	*tmp;

  if (!(egg = malloc(sizeof(t_egg))))
    error("malloc");
  egg->id = id;
  egg->pos[X] = pos[X];
  egg->pos[Y] = pos[Y];
  content->nbr_egg++;
  egg->nbr = content->nbr_egg;
  tmp = content->clients;
  while (tmp)
    {
      if (tmp->trigger[GRAPHIC] == true)
	ssend(tmp->socket, "enw %d %d %lu %lu\n", egg->nbr, id, egg->pos[X],
	      egg->pos[Y]);
      tmp = tmp->next;
    }
  push_egg(&team->eggs, egg);
}
