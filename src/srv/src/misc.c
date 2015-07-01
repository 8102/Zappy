/*
** misc.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:59:24 2015 Emmanuel Chambon
** Last update Fri Jun 19 16:50:54 2015 Emmanuel Chambon
*/

#include "zappy.h"

void		error(char *error)
{
  perror(error);
  exit(EXIT_FAILURE);
}

char		*str_replace(char *str, char target, char replace)
{
  int		i;

  for (i = 0; str[i]; i++)
    if (str[i] == target)
      str[i] = replace;
  return (str);
}

t_case		*getCaseFromCoord(size_t x, size_t y, t_case *all)
{
  while (all)
    {
      if (x == all->x && y == all->y)
	return (all);
      all = all->next;
    }
  return (NULL);
}

char		*transform_int(int tmp)
{
  char		*str;
  int		size;
  int		i;

  i = 0;
  size = 1;
  while (tmp / pow(10, size) != 0)
    size++;
  if (!(str = malloc(size + 1)))
    return (NULL);
  while (i < size)
    {
      str[i++] = tmp % 10;
      tmp /= 10;
    }
  str[i] = 0;
  return (str);
}
