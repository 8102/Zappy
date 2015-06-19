/*
** server_idle.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:48:27 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:51:41 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		watch_sockets(int *i, int *max, fd_set *catch,
			      t_master *content)
{
  if (FD_ISSET(*i, catch))
    {
      if (*i == content->server.socket)
	handle_new_connection(max, content);
      else
	handle_io_connection(get_client(*i, &(content->clients)), content);
    }
}

void		idle_server(t_master *content)
{
  t_server	*serv;
  fd_set	catch;
  int		max;
  int		i;

  serv = &(content->server);
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
	watch_sockets(&i, &max, &catch, content);
    }
}
