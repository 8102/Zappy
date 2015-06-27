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

t_case		*getCaseInMap(int x, int y, t_case *tmp, t_master *all)
{
  t_case	*parse;

  if (y < 0 || y > all->height || x < 0 || x > all->width)
    return (tmp);
  parse = (tmp) ? tmp : all->cases;
  while (parse->x != (size_t)x || parse->y != (size_t)y)
    parse = parse->next;
  return (parse);
}

int		countHowMany(t_case *tmp)
{
  int		count;

  count = 0;
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
  str = realloc(str, countHowMany(tmp) + 3);
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
