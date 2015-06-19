/*
** client_handler.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 14:42:29 2015 Emmanuel Chambon
** Last update Fri Jun 19 17:00:44 2015 Emmanuel Chambon
*/

#include "zappy.h"

void				handle_new_connection(int *max,
						      t_master *content)
{
  t_server			*serv;
  struct sockaddr_storage	r;
  socklen_t			len;
  char				ip[INET6_ADDRSTRLEN];
  t_client			*client;

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
  client->buffer = cb_init();
  client->recv = rb_init();
  client->auth = false;
  client->graphic = false;
  push_client(&(content->clients), client);
  ssend(client->socket, "BIENVENUE\n");
}

t_client	*get_client(int socket, t_client **clients)
{
  t_client	*tmp;

  for (tmp = *clients; tmp; tmp = tmp->next)
    if (tmp->socket == socket)
      return (tmp);
  return (NULL);
}

void		remove_connection(t_client *client, t_master *content, int rc)
{
  (rc == 0) ? printf("%s Disconnected\n", client->ip) : perror("recv");
  FD_CLR(client->socket, &content->server.master);
  pop_client(&content->clients, client);
}

void		input_interpret(t_client *client, t_master *content)
{
  char		*input;
  int		i;

  input = cb_read(client->buffer);
  printf("[%s]\n", input);
  for (i = 0; i < MAX_CMD - 1; i++)
    {
      if (!client->auth)
	continue ;
      if (!(strncmp(content->server.cmd[i],
		    input, strlen(content->server.cmd[i]))))
	content->server.cmd_handler[i](epur_str(strchr(input, ' ')),
				       client, content);
    }
  if (i == MAX_CMD - 1 && !client->auth)
    select_team(input, client, content);
  free(input);
}

void		handle_io_connection(t_client *client, t_master *content)
{
  char		tmp[RB_SIZE];
  int		rc;

  if (!client)
    return ;
  memset(tmp, 0, RB_SIZE);
  if ((rc = recv(client->socket, tmp, RB_SIZE, 0)) > 0)
    {
      rb_write(client->recv, tmp);
      if (rb_at(client->recv, -1) == '\n')
	{
	  rb_delete_last(client->recv);
	  if (!cb_available(client->buffer))
	    rb_reset(client->recv);
	  else
	    {
	      cb_write(client->buffer, epur_str(str_replace(rb_read(client->recv),
							    '\n', '\0')), false);
	      input_interpret(client, content);
	    }
	}
    }
  else
    remove_connection(client, content, rc);
}
