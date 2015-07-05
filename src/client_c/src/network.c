/*
** network.c for Zappy in /home/tommy/Dropbox/Epitech/2ème Année/PSU_2014_zappy/src/client_c/
**
** Made by TommyStarK
** Login   <milox_t@epitech.eu>
**
** Started on  Sat Jun 27 20:48:42 2015 TommyStarK
** Last update Sun Jul  5 21:09:25 2015 Emmanuel Chambon
*/

#include "client.h"

void		*ipvx(struct sockaddr *s)
{
  if (s->sa_family == AF_INET)
    return &(((struct sockaddr_in*)s)->sin_addr);
  return &(((struct sockaddr_in6*)s)->sin6_addr);
}

void		disconnect(t_client *it)
{
   if (it->status)
     close(it->client->fd);
   if (write(1, BYEBYE, strlen(BYEBYE)) == -1)
     error("write");
   exit(EXIT_SUCCESS);
}

int		co_serv(t_socket *s, const char *ip, const char *port)
{
  addinf	hints;
  addinf	*info;
  addinf	*l;
  int		ret;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((ret = getaddrinfo(ip, port, &hints, &info)) != 0)
    error("getaddrinfo");
  l = info;
  while (l)
    {
      if ((s->fd = socket(l->ai_family, l->ai_socktype, l->ai_protocol)) == -1)
        l = l->ai_next;
      if (connect(s->fd, l->ai_addr, l->ai_addrlen) == -1)
        l = l->ai_next;
      break ;
    }
  freeaddrinfo(info);
  return (!l ? 0 : 1);
}
