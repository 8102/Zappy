/*
** client.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 22:07:25 2015 Emmanuel Chambon
** Last update Thu Jun 18 14:42:52 2015 Emmanuel Chambon
*/

#include "zappy.h"

void            push_client(t_client **list, t_client *elem)
{
  t_client      *it;
  t_client      *save;
  bool          stop;

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

void		delete_client(t_client *client)
{
  if (!client)
    return ;
  if (client->ip)
    free(client->ip);
  rb_free(client->buffer);
  if (client->socket)
    close(client->socket);
  free(client);
}

void            pop_client(t_client **list, t_client *elem)
{
  t_client      *it;
  t_client      *prev;

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
	  delete_client(elem);
	  return ;
	}
      if (it != *list)
	prev = prev->next;
      it = it->next;
    }
}

void		release_clients(t_client **clients)
{
  t_client	*tmp;
  t_client	*prv;

  prv = NULL;
  tmp = *clients;
  while (tmp)
    {
      printf("%d\n", tmp->socket);
      if (prv)
	delete_client(prv);
      prv = tmp;
      tmp = tmp->next;
    }
  delete_client(prv);
}
