/*
** server.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:30:20 2015 Emmanuel Chambon
** Last update Tue Jun 16 20:20:21 2015 Emmanuel Chambon
*/

#include "zappy.h"

void			close_handler(int sig)
{
  if (sig == SIGINT)
    g_run = false;
}

void			release_server(t_server *serv)
{
  if (serv && serv->port)
    free(serv->port);
  if (serv && serv->socket)
    close(serv->socket);
}

void			set_server(t_server *serv, char *port)
{
  serv->port = strdup(port);
  serv->socket = bind_port(port);
  FD_ZERO(&serv->master);
  FD_SET(serv->socket, &serv->master);
  set_handler(serv);
}

void			init_server(t_server *serv, char *port)
{
  struct sigaction	si;

  set_server(serv, port);
  g_run = true;
  si.sa_handler = close_handler;
  sigemptyset(&si.sa_mask);
  si.sa_flags = SA_RESTART;
  if (sigaction(SIGINT, &si, NULL) == -1)
    {
      fprintf(stderr, "Warning: sigaction failed: %s\n", strerror(errno));
      fprintf(stderr, "Memory will not be freed and socket won't be close");
      fprintf(stderr, " at server close\n");
    }
}
