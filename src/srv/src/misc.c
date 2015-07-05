/*
** misc.c for  in /home/chambo_e/epitech/PSU_2014_zappy/src/srv
**
** Made by Emmanuel Chambon
** chambo_e  <chambon.emmanuel@gmail.com>
**
** Started on  Tue Jun 16 11:59:24 2015 Emmanuel Chambon
** Last update Sun Jul  5 17:19:46 2015 Hugo Prenat
*/

#include "zappy.h"

_Noreturn void		error(char *error)
{
  perror(error);
  exit(EXIT_FAILURE);
}

char		*str_replace(char *str, char target, char replace)
{
  for (int i = 0; str[i]; i++)
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

char		*revstr(char *str)
{
  char		*revd;
  int		i;
  int		j;

  j = 0;
  if (!(revd = malloc(strlen(str) + 1)))
    error("malloc");
  i = strlen(str) - 1;
  while (i >= 0)
    {
      revd[j] = str[i];
      i--;
      j++;
    }
  revd[j] = 0;
  return (revd);
}

char		*transform_int(int tmp)
{
  char		*str;
  int		size;
  int		i;
  int		mult;

  i = 0;
  size = 1;
  mult = 10;
  while (tmp / mult != 0)
    {
      size++;
      mult *= 10;
    }
  if (!(str = malloc(size + 1)))
    error("malloc");
  while (i < size)
    {
      str[i++] = tmp % 10 + '0';
      tmp /= 10;
    }
  str[i] = 0;
  printf("%s\n", str);
  return (revstr(str));
}
