/*
** server_idle.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:48:27 2015 Emmanuel Chambon
** Last update Sat Jul  4 00:00:09 2015 Emmanuel Chambon
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

void			client_lookup(t_master *content)
{
  static ull		time_unit = 0;
  bool			remove_food;

  remove_food = false;
  time_unit++;
  if (!(time_unit % 1260))
    remove_food = !remove_food;
  timespec_update(content->time.pl_now);
  for (t_client *tmp = content->clients; tmp; tmp = tmp->next)
    {
      if (!tmp->trigger[AUTH])
	continue ;
      if (remove_food)
	tmp->resources[MEAL]--;
      /* if (tmp->resources[MEAL]--) */
      /* 	die_player_die(tmp); */
      if (cb_available(tmp->buffer) < CB_SIZE &&
	  timespec_is_greater(content->time.pl_now, tmp->clock))
	input_interpret(tmp, content);
    }
}

void		idle_server(t_master *content)
{
  t_server	*serv;
  fd_set	catch;
  int		max;
  int		r;

  serv = &(content->server);
  max = serv->socket;
  FD_ZERO(&catch);
  while (g_run)
    {
      catch = serv->master;
      if ((r = (pselect(max + 1, &catch, NULL, NULL,
			content->time.timeout, NULL))) == -1)
	{
	  if (!g_run)
	    return ;
	  error("select");
	}
      if (!r)
	  client_lookup(content);
      else
	for (int i = 0; i <= max; i++)
	  watch_sockets(&i, &max, &catch, content);
    }
}
