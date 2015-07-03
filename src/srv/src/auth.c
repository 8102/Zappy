/*
** welcome.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 15:01:28 2015 Emmanuel Chambon
** Last update Fri Jul  3 03:32:15 2015 Emmanuel Chambon
*/

#include "zappy.h"

void                            handle_new_connection(int *max,
						      t_master *content)
{
  t_server                      *serv;
  struct sockaddr_storage       r;
  socklen_t                     len;
  char                          ip[INET6_ADDRSTRLEN];
  t_client                      *client;

  if (!(client = malloc(sizeof(t_client))))
    error("malloc");
  memset(client, 0, sizeof(*client));
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
  init_client(client, content);
  push_client(&(content->clients), client);
  ssend(client->socket, "BIENVENUE\n");
}

void            remove_connection(t_client *client, t_master *content, int rc)
{
  (rc == 0) ? printf("%s Disconnected\n", client->ip) : perror("recv");
  FD_CLR(client->socket, &content->server.master);
  pop_client(&content->clients, client);
}

t_team		*find_team(char *team_name, t_master *content)
{
  for (t_team *tmp = content->teams; tmp; tmp = tmp->next)
    if (!strcmp(tmp->name, team_name))
      return (tmp);
  return (NULL);
}

void		select_team(char *team, t_client *client, t_master *content)
{
  t_team	*tm;

  if (!(tm = find_team(team, content)))
    ssend(client->socket, "0\n");
  else
    {
      if (tm->slot == 0)
	ssend(client->socket, "0\n");
      else
	{
	  ssend(client->socket, "%d\n", tm->slot);
	  client->team = tm;
	  place_player(content, client);
	  client->team->slot--;
	}
    }
  ssend(client->socket, "%d %d\n", content->width, content->height);
}
