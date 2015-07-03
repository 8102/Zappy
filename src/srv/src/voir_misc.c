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

t_case		*getNextCase(t_case *tmp, t_master *all, int type)
{
  if (type == 0)
    {
      if (tmp->x + 1 >= all->width)
	return (getCaseFromCoord(0, tmp->y, all->cases));
      return (getCaseFromCoord(tmp->x + 1, tmp->y, all->cases));
    }
  if (tmp->y + 1 >= all->height)
    return (getCaseFromCoord(tmp->x, 0, all->cases));
  return (getCaseFromCoord(tmp->x, tmp->y + 1, all->cases));
}

t_case		*getCaseInMap(t_client *client, int tmp, int lvl, t_master *all)
{
  t_case	*parse;
  size_t		x;
  size_t		y;

  x = client->pos[0] + tmp;
  if (x >= all->width)
    x -= all->width;
  y = client->pos[1] + lvl;
  if (y >= all->height)
    y-= all->height;
  parse = all->cases;
  while (parse && (parse->x != (size_t)x || parse->y != (size_t)y))
    parse = parse->next;
  return (parse);
}

int		countHowMany(t_case *tmp)
{
  int		count;

  count = 0;
  if (tmp->nbr_player > 0)
    count += 8;
  if (tmp->meal > 0)
    count += 11;
  if (tmp->linemate > 0)
    count += 10;
  if (tmp->deraumere > 0)
    count += 10;
  if (tmp->sibur > 0)
    count += 6;
  if (tmp->mendiane > 0)
    count += 9;
  if (tmp->phiras > 0)
    count += 7;
  if (tmp->thystame > 0)
    count += 10;
  return (count);
}

char		*fillStringCase(t_case *tmp, char *str)
{
  str = realloc(str, countHowMany(tmp) + 3 + strlen(str));
  if (tmp->nbr_player > 0)
    strcat(str, " joueur");
  if (tmp->meal > 0)
    strcat(str, " nourriture");
  if (tmp->linemate > 0)
    strcat(str, " linemate");
  if (tmp->deraumere > 0)
    strcat(str, " deraumere");
  if (tmp->sibur > 0)
    strcat(str, " sibur");
  if (tmp->mendiane > 0)
    strcat(str, " mendiane");
  if (tmp->phiras > 0)
    strcat(str, " phiras");
  if (tmp->thystame > 0)
    strcat(str, " thystame");
  return (str);
}

char		*fillFirstTime()
{
  char		*to_write;

  if (!(to_write = malloc(5)))
    return (NULL);
  bzero(to_write, 4);
  to_write[0] = '{';
  return (to_write);
}
