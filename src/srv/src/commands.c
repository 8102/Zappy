/*
** commands.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 08:31:10 2015 Emmanuel Chambon
** Last update Thu Jun 18 01:36:13 2015 Emmanuel Chambon
*/

#include "zappy.h"

void			avance(bool (*check)(char*),
			       char *params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "ok\n");
}

void			droite(bool (*check)(char*),
			       char *params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "ok\n");
}

void			gauche(bool (*check)(char*),
			       char *params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "ok\n");
}

void			voir(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
}

void			inventaire(bool (*check)(char*),
				   char *params,
				   t_client *client,
				   __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "linemate %d, deraumère %d, sibur %d, mendiane %d, phiras %d, thystame %d\n", 0, 0, 0, 0, 0, 0);
}

void			prend(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
}

void			pose(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
}

void			expulse(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
}

void			broadcast(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "ok\n");
}

void			incantation(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "elevation en cours\nniveau actuel : %d\n", 0);
}

void			_fork(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "ok\n");
}

void			connect_nbr(bool (*check)(char*),
			     char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!check(params))
    {
      ssend(client->socket, "suc\n");
    }
  ssend(client->socket, "%d\n", content->teams->slot);
}
