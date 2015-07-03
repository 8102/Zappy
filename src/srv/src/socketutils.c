/*
** socketutils.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:46:03 2015 Emmanuel Chambon
** Last update Sat Jul  4 01:09:31 2015 Hugo Prenat
*/

#include "zappy.h"

void		ssend_graphics(t_master *content, char *msg, ...)
{
  va_list	args;
  t_client	*client_tmp;

  va_start(args, msg);
  client_tmp = content->clients;
  while (client_tmp)
    {
      if (client_tmp->trigger[GRAPHIC])
	{
	  if (!(vdprintf(client_tmp->socket, msg, args)))
	    error("dprintf");
	}
      client_tmp = client_tmp->next;
    }
  va_end(args);
}

void		ssend(int socket, char *msg, ...)
{
  va_list	args;

  va_start(args, msg);
  if (!(vdprintf(socket, msg, args)))
    error("dprintf");
  va_end(args);
}

void		*ipvx(struct sockaddr *s)
{
  if (s->sa_family == AF_INET)
    return &(((struct sockaddr_in*)s)->sin_addr);
  return &(((struct sockaddr_in6*)s)->sin6_addr);
}

int		bind_local(struct addrinfo *i, int *sock)
{
  int		trigger;

  trigger = 1;
  if ((*sock = socket(i->ai_family, i->ai_socktype, i->ai_protocol)) == -1)
    return (1);
  if (setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &trigger, sizeof(trigger)))
    return (1);
  if (bind(*sock, i->ai_addr, i->ai_addrlen) == -1)
    {
      close(*sock);
      return (1);
    }
  return (0);
}

int			bind_port(char *port)
{
  struct addrinfo	h;
  struct addrinfo	*s;
  struct addrinfo	*i;
  int			sock;

  memset(&h, 0, sizeof(struct addrinfo));
  h.ai_family = AF_UNSPEC;
  h.ai_socktype = SOCK_STREAM;
  h.ai_flags = AI_PASSIVE;
  if (getaddrinfo(NULL, port, &h, &s))
    error("getaddrinfo");
  for (i = s; i != NULL; i = i->ai_next)
    {
      if (!bind_local(i, &sock))
	break ;
    }
  if (!i)
    error("bind");
  freeaddrinfo(s);
  if (listen(sock, BACKLOG))
    error("listen");
  return (sock);
}
