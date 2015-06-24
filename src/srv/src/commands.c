/*
** commands.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Wed Jun 17 08:31:10 2015 Emmanuel Chambon
** Last update Wed Jun 24 15:26:13 2015 Hugo Prenat
*/

#include "zappy.h"

void			avance(char __attribute__((unused))*params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  /* if (!check(params)) */
  /*   { */					// NO Need to check parameters. There is none
  /*     ssend(client->socket, "suc\n"); */
  /*   } */
  ssend(client->socket, "ok\n");
}

void			droite(char __attribute__((unused))*params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "ok\n");
}

void			gauche(char __attribute__((unused))*params,
			       t_client *client,
			       __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "ok\n");
}

void			voir(char __attribute__((unused))*params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
}

void			inventaire(char __attribute__((unused))*params,
				   t_client *client,
				   __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "linemate %d, deraumère %d, sibur %d, mendiane %d, phiras %d, thystame %d\n", 0, 0, 0, 0, 0, 0);
}

void			prend(char *params,
			      t_client *client,
			      __attribute__((unused)) t_master *content)
{
  if (!params)
    {
      ssend(client->socket, "suc\n");
      return ;
    }
}

void			pose(char *params,
			     t_client *client,
			     __attribute__((unused)) t_master *content)
{
  if (!params)
    {
      ssend(client->socket, "suc\n");
      return ;
    }
}

void			expulse(char __attribute__((unused))*params,
				t_client *client,
				__attribute__((unused)) t_master *content)
{
}

void			broadcast(char *params,
				  t_client *client,
				  __attribute__((unused)) t_master *content)
{
  if (!params)
    {
      ssend(client->socket, "suc\n");
      return ;
    }
  ssend(client->socket, "ok\n");
}

void			incantation(char __attribute__((unused))*params,
				    t_client *client,
				    __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "elevation en cours\nniveau actuel : %d\n", 0);
}

void			_fork(char __attribute__((unused))*params,
			      t_client *client,
			      __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "ok\n");
}

void			connect_nbr(char __attribute__((unused))*params,
				    t_client *client,
				    __attribute__((unused)) t_master *content)
{
  ssend(client->socket, "%d\n", client->team->slot);
}

void			msz(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			bct(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			mct(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			tna(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			ppo(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			plv(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			pin(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			sgt(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}

void			sst(char __attribute__((unused))*params,
				    t_client __attribute__((unused))*client,
				    __attribute__((unused)) t_master *content)
{

}
