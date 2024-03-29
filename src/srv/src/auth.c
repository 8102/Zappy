/*
** welcome.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv/src
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Thu Jun 18 15:01:28 2015 Emmanuel Chambon
** Last update Sun Jul  5 23:10:42 2015 Emmanuel Chambon
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
  set_mineral(((int)MEAL) + 1,
	      (content->width * content->height) / 2, content);
}

void		remove_connection(t_client *client, t_master *content, int rc)
{
  t_case	*case_tmp;

  (rc == 0) ? printf("%s%s%s Disconnected%s\n", BOLDCYAN, client->ip,
		     BOLDYELLOW, RESET) : perror("recv");
  FD_CLR(client->socket, &content->server.master);
  if (client->trigger[AUTH])
    ssend_graphics(content, "pdi %d\n", client->id);
  case_tmp = getCaseFromCoord(client->pos[X], client->pos[Y], content->cases);
  case_tmp->content[0]--;
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
      if (tm->slot > 0 || has_egg_eclos(tm))
	{
	  ssend(client->socket, "%d\n", tm->slot);
	  client->team = tm;
	  place_player(content, client);
	  client->team->slot--;
	}
      else
	ssend(client->socket, "0\n");
    }
  ssend(client->socket, "%d %d\n", content->width, content->height);
}
