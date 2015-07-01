/*
** voir.c for in /home/rendu/PSU_2014_zappy/src/srv
**
** Made by David Tran
** tran_0  <david.tran@epitech.eu>
**
** Started on  Wed Jun 17 08:31:10 2015 David Tran
** Last update Wed Jun 24 15:26:13 2015 David Tran
*/

#include "zappy.h"

char		*getUpAndDownVision(t_client *client, t_master *all, int lvl)
{
  int		tmp;
  t_case	*position;
  char		*to_write;

  tmp = (lvl < 0) ? lvl : lvl * -1;
  while (tmp + (int)client->pos[0] < 0)
    tmp++;
  position = getCaseInMap(client, tmp, lvl, all);
  if (lvl != 0)
    to_write = getUpAndDownVision(client, all,
				  (lvl < 0) ? lvl + 1 : lvl - 1);
  else
    if (!(to_write = fillFirstTime()))
      return (NULL);
  while (position && tmp <= ((lvl < 0) ? lvl * -1 : lvl))
    {
      to_write = fillStringCase(position, to_write);
      getNextCase(position, all, 0);
      (tmp == client->level) ?
	strcat(to_write, "") : strcat(to_write, ",");
      tmp++;
    }
  if (((lvl < 0) ? lvl * -1 : lvl) == client->level)
    strcat(to_write, "}\n");
  return (to_write);
}

char	*getLeftAndRightVision(t_client *client, t_master *all, int lvl)
{
  int		tmp;
  t_case	*position;
  char		*to_write;

  tmp = (lvl < 0) ? lvl : lvl * -1;
  while (tmp + (int)client->pos[0] < 0)
    tmp++;
  position = getCaseInMap(client, lvl, tmp, all);
  if (lvl != 0)
    to_write = getUpAndDownVision(client, all,
				  (lvl < 0) ? lvl + 1 : lvl - 1);
  else
    if (!(to_write = fillFirstTime()))
      return (NULL);
  while (position && tmp <= ((lvl < 0) ? lvl * -1 : lvl))
    {
      to_write = fillStringCase(position, to_write);
      getNextCase(position, all, 1);
      (tmp == client->level) ?
	strcat(to_write, "") : strcat(to_write, ",");
      tmp++;
    }
  ((lvl < 0) ? lvl * -1 : lvl == client->level) ?
    strcat(to_write, "\n") : strcat(to_write, ",");
  return (to_write);
}

void	select_position_watch(t_client *client, t_master *all)
{
  char	*to_free;

  to_free = NULL;
  if (client->orient == NORTH || client->orient == SOUTH)
    to_free = getUpAndDownVision(client, all, (client->orient == NORTH) ?
				 -1 * (client->level) : client->level);
  else
    to_free = getLeftAndRightVision
      (client, all, (client->orient == EAST)
       ? -1 * (client->level) : client->level);
  if (to_free)
    {
      ssend(client->socket, to_free);
      free(to_free);
    }
}
