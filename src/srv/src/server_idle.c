/*
** server_idle.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:48:27 2015 Emmanuel Chambon
** Last update Thu Jun 18 01:34:43 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		input_interpret(t_client *client, t_all *content)
{
  char		*input;
  int		i;

  input = rb_read(client->buffer);
  for (i = 0; i < MAX_CMD - 1; i++)
    {
      if (!(strncmp(content->server.cmd[i],
		    input, strlen(content->server.cmd[i]))))
	content->server.cmd_handler[i](NULL, input, client, content);
    }
  free(input);
}

void		handle_io_connection(t_client *client, t_all *content)
{
  char		tmp[RECV_SIZE];
  int           rc;

  if (!client)
    return ;
  memset(tmp, 0, RECV_SIZE);
  if ((rc = recv(client->socket, tmp, RECV_SIZE, 0)) > 0)
    {
      rb_write(client->buffer, tmp);
      input_interpret(client, content);
    }
  else
    {
      if (rc == 0)
	printf("%s Disconnected\n", client->ip);
      else
	perror("recv");
      FD_CLR(client->socket, &content->server.master);
      remove_connection(client, content);
    }
}

void            watch_sockets(int *i, int *max, fd_set *catch, t_all *content)
{
  if (FD_ISSET(*i, catch))
    {
      if (*i == content->server.socket)
	handle_new_connection(max, content);
      else
	handle_io_connection(get_client(*i, content), content);
    }
}

void            idle_server(t_all *content)
{
  t_server	*serv;
  fd_set        catch;
  int           max;
  int           i;

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
