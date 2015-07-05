/*
** server_idle.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:48:27 2015 Emmanuel Chambon
** Last update Sun Jul  5 18:48:35 2015 Emmanuel Chambon
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

void			lookup(t_client **tmp, bool remove_food,
			       t_master *content)
{
  t_client		*prev;

  if (!(*tmp)->trigger[AUTH])
    {
      (*tmp) = (*tmp)->next;
      return ;
    }
  if (remove_food)
    (*tmp)->resources[MEAL]--;
  if (!(*tmp)->resources[MEAL])
    {
      prev = (*tmp);
      (*tmp) = (*tmp)->next;
      remove_connection(prev, content, 0);
      return ;
    }
  if (cb_available((*tmp)->buffer) < CB_SIZE &&
      timespec_is_greater(content->time.pl_now, (*tmp)->clock))
    input_interpret((*tmp), content);
  if ((*tmp)->level == MAX_LEVEL)
    (*tmp)->team->leveled_pl++;
  (*tmp) = (*tmp)->next;
}

void			client_lookup(t_master *content)
{
  static ull		time_unit = 0;
  bool			remove_food;
  t_client		*tmp;

  remove_food = false;
  time_unit++;
  if (!(time_unit % 126))
    remove_food = !remove_food;
  reset_leveled(content);
  timespec_update(content->time.pl_now);
  tmp = content->clients;
  while (tmp)
    lookup(&tmp, remove_food, content);
  check_leveled(content);
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
