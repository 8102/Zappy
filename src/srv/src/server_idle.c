/*
** server_idle.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:48:27 2015 Emmanuel Chambon
** Last update Tue Jun 16 12:17:54 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		handle_new_connection(int __attribute__((unused))*max, t_server *serv)
{
  struct sockaddr_storage       r;
  socklen_t                     len;
  char                          ip[INET6_ADDRSTRLEN];
  int				socket; // TEMP

  len = sizeof(r);
  if ((socket = accept(serv->socket, (struct sockaddr *)&r, &len)) == -1)
    error("accept");
  FD_SET(socket, &serv->master);
  printf("ip = %s\n", inet_ntop(r.ss_family, ipvx((struct sockaddr *)&r),
			      ip, INET6_ADDRSTRLEN));
  dprintf(socket, "hello");
}

void            watch_sockets(int *i, int *max, fd_set *catch, t_server *serv)
{
  if (FD_ISSET(*i, catch))
    {
      if (*i == serv->socket)
	handle_new_connection(max, serv);
      printf("va y ! tape moi dans le select !\n");
    }
}

void            idle_server(t_server *serv)
{
  fd_set        catch;
  int           max;
  int           i;

  max = serv->socket;
  FD_ZERO(&catch);
  while (g_run)
    {
      catch = serv->master;
      if (select(max + 1, &catch, NULL, NULL, NULL) == -1)
	{
	  if (!g_run)
	    return ;
	  error("select");
	}
      for (i = 0; i <= max; i++)
	watch_sockets(&i, &max, &catch, serv);
    }
}
