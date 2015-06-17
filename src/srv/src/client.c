/*
** client.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 22:07:25 2015 Emmanuel Chambon
** Last update Thu Jun 18 01:28:37 2015 Emmanuel Chambon
*/

#include "zappy.h"

void            handle_new_connection(int *max, t_all *content)
{
  t_server                      *serv;
  struct sockaddr_storage       r;
  socklen_t                     len;
  char                          ip[INET6_ADDRSTRLEN];
  t_client                      *client;

  if (!(client = malloc(sizeof(t_client))))
    error("malloc");
  serv = &(content->server);
  len = sizeof(r);
  if ((client->socket = accept(serv->socket, (struct sockaddr *)&r,
			       &len)) == -1)
    error("accept");
  FD_SET(client->socket, &serv->master);
  if (client->socket > *max)
    *max = client->socket;
  client->ip = strdup(inet_ntop(r.ss_family, ipvx((struct sockaddr *)&r),
				ip, INET6_ADDRSTRLEN));
  client->orient = NORTH;
  client->buffer = rb_init();
  push_client(&content->clients, client);
}

t_client        *get_client(int socket, t_all *content)
{
  t_client      *tmp;

  for (tmp = content->clients; tmp; tmp = tmp->next)
    if (tmp->socket == socket)
      return (tmp);
  return (NULL);
}

void            remove_connection(t_client *client, t_all *content)
{
  pop_client(&content->clients, client);
}

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
	  if (elem->ip)
	    free(elem->ip);
	  rb_free(elem->buffer);
	  free(elem);
	  return ;
	}
      if (it != *list)
	prev = prev->next;
      it = it->next;
    }
}
