/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Sun Jul  5 22:42:14 2015 Emmanuel Chambon
*/

#include "zappy.h"

bool	check_level(t_client *client, t_master *content, int need[7][7])
{
  t_client	*tmp;
  int		tot;

  tot = 0;
  for (tmp = content->clients; tmp; tmp = tmp->next)
    {
      if (!tmp->trigger[AUTH])
	continue ;
      if (tmp->pos[X] == client->pos[X] && tmp->pos[Y] == client->pos[Y]
	  && tmp->level == client->level)
	tot++;
    }
  if (need[client->level - 1][0] == tot)
    return (true);
  return (false);
}

bool	check_stones(t_client *client, t_master *content, int need[7][7])
{
  t_case	*tmp;
  int		i;

  if (!(tmp = getCaseFromCoord(client->pos[X], client->pos[Y], content->cases)))
    return (false);
  for (i = 1; i < 7; i++)
    if (tmp->content[i] != need[client->level - 1][i])
      return (false);
  return (true);
}

char		*incantation_done(t_client *client, t_master *content,
				  int need[7][7])
{
  t_client	*tmp;
  char		*ids;
  char		ttmp[25];

  if (!(ids = malloc(need[client->level - 1][0] * 10 * sizeof(char))))
    error("malloc");
  memset(ids, 0, need[client->level - 1][0] * 10 * sizeof(char));
  for (tmp = content->clients; tmp; tmp = tmp->next)
    {
      memset(ttmp, 0, 25);
      if (tmp->level != client->level)
	continue ;
      ssend(tmp->socket, "elevation en cours\nniveau actuel: %d\n", tmp->level);
      sprintf(ttmp, "%d ", tmp->id);
      strcat(ids, ttmp);
      tmp->level++;
    }
  return (ids);
}

void	incantation_graphic_done(t_client *client, t_master *content)
{

}

void		incantation(char UNUSED*params,
			    t_client *client,
			    t_master *content)
{
  static int	need[7][7] = {{1, 1, 0, 0, 0, 0, 0},
			      {2, 1, 1, 1, 0, 0, 0},
			      {2, 2, 0, 1, 0, 2, 0},
			      {4, 1, 1, 2, 0, 1, 0},
			      {4, 1, 2, 1, 3, 0, 0},
			      {6, 1, 2, 3, 0, 1, 0},
			      {6, 2, 2, 2, 2, 2, 1}};
  bool		ok;
  char		*ids;

  if ((ok = check_level(client, content, need)))
    ok = check_stones(client, content, need);
  if (!ok)
    ssend(client->socket, "ko\n");
  else
    {
      ids = incantation_done(client, content, need);
      ssend_graphics(content, "pic %d %d %d %s\n", client->pos[X],
		     client->pos[Y], client->level - 1, ids);
      incantation_graphic_done(client, content);
    }
}
